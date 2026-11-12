// Export exact existing functions from an analysis project without executing firmware.
// @category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class ExportFunctions extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) throw new IllegalArgumentException("output directory, function addresses...");
        File directory = new File(args[0]);
        directory.mkdirs();
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        try (PrintWriter graph = new PrintWriter(new File(directory, "calls.tsv"));
             PrintWriter refs = new PrintWriter(new File(directory, "entry-references.tsv"));
             PrintWriter listing = new PrintWriter(new File(directory, "instructions.txt"))) {
            for (int n = 1; n < args.length; n++) {
                Address entry = toAddr(Long.parseUnsignedLong(args[n].replaceFirst("^0x", ""), 16));
                Function function = getFunctionAt(entry);
                if (function == null) throw new IllegalArgumentException("No existing function at " + entry);
                DecompileResults result = decompiler.decompileFunction(function, 60, monitor);
                if (!result.decompileCompleted()) throw new IOException("Decompile failed: " + entry + " " + result.getErrorMessage());
                try (PrintWriter output = new PrintWriter(new File(directory, entry + ".c"))) {
                    output.println("// Ghidra " + getGhidraVersion() + "; synthetic ELF; " + entry);
                    output.println(result.getDecompiledFunction().getC().replaceAll("(?m)[ \\t]+$", "").stripTrailing());
                }
                ArrayList<Function> called = new ArrayList<>(function.getCalledFunctions(monitor));
                called.sort(Comparator.comparing(Function::getEntryPoint));
                for (Function callee : called) graph.println(entry + "\t" + callee.getEntryPoint());
                ReferenceIterator incoming = currentProgram.getReferenceManager().getReferencesTo(entry);
                while (incoming.hasNext()) {
                    Reference ref = incoming.next();
                    Function caller = getFunctionContaining(ref.getFromAddress());
                    refs.println(entry + "\t" + ref.getFromAddress() + "\t" + ref.getReferenceType() + "\t" + (caller == null ? "-" : caller.getEntryPoint()));
                }
                listing.println("FUNCTION " + entry);
                InstructionIterator instructions = currentProgram.getListing().getInstructions(function.getBody(), true);
                while (instructions.hasNext()) {
                    Instruction instruction = instructions.next();
                    listing.println(instruction.getAddress() + "  " + instruction);
                    for (Reference ref : instruction.getReferencesFrom()) {
                        listing.println("  -> " + ref.getToAddress() + " " + ref.getReferenceType());
                        if (ref.getReferenceType().isRead()) {
                            try {
                                int word = getInt(ref.getToAddress());
                                listing.printf("     word=0x%08x%n", word);
                            } catch (Exception ignored) { }
                        }
                    }
                }
            }
        } finally {
            decompiler.dispose();
        }
    }
}
