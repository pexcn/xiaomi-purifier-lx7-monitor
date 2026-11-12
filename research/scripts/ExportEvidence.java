// Ghidra 12 post-script: export actual decompiler output, references and listing.
// @category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;

public class ExportEvidence extends GhidraScript {
    public void run() throws Exception {
        File directory = new File(getScriptArgs()[0]);
        directory.mkdirs();
        // These 16 exact function pointers are present in the image delegate table.
        for (int i = 0; i < 16; i++) {
            Address entry = toAddr(Integer.toUnsignedLong(getInt(toAddr(0x3ffe8c00L + 8*i))));
            if (getFunctionAt(entry) == null) {
                disassemble(entry);
                createFunction(entry, null);
            }
        }
        for (int i = 0; i < 30; i++) {
            Address entry = toAddr(Integer.toUnsignedLong(getInt(toAddr(0x3ffe8a88L + 12*i))));
            if (getFunctionAt(entry) == null) {
                disassemble(entry);
                createFunction(entry, null);
            }
        }
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        try (PrintWriter inventory = new PrintWriter(new File(directory, "functions.tsv"));
             PrintWriter refs = new PrintWriter(new File(directory, "references.tsv"));
             PrintWriter listing = new PrintWriter(new File(directory, "bridge-listing.txt"))) {
            FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
            while (functions.hasNext()) {
                Function function = functions.next();
                long address = function.getEntryPoint().getOffset();
                inventory.println(function.getEntryPoint()+"\t"+function.getName()+"\t"+function.getBody());
                if ((address >= 0x4023d000L && address < 0x4024e200L) ||
                    (address >= 0x40257200L && address < 0x40257400L) ||
                    (getScriptArgs().length > 1 && getScriptArgs()[1].equals("all"))) {
                    DecompileResults result = decompiler.decompileFunction(function, 30, monitor);
                    try (PrintWriter output = new PrintWriter(new File(directory, function.getEntryPoint()+".c"))) {
                        output.println("// Ghidra " + getGhidraVersion() + "; synthetic ELF; " + function.getEntryPoint());
                        if (result.decompileCompleted()) {
                            String body = result.getDecompiledFunction().getC();
                            // Only normalize trailing whitespace; preserve all code and names.
                            output.println(body.replaceAll("(?m)[ \\t]+$", "").stripTrailing());
                        }
                        else output.println("// DECOMPILATION FAILED: " + result.getErrorMessage());
                    }
                }
            }
            InstructionIterator instructions = currentProgram.getListing().getInstructions(true);
            while(instructions.hasNext()) {
                Instruction instruction = instructions.next();
                long a = instruction.getAddress().getOffset();
                if (a >= 0x40243000L && a < 0x4024e000L) listing.println(instruction.getAddress()+"  "+instruction);
            }
            ReferenceIterator references = currentProgram.getReferenceManager().getReferenceIterator(toAddr(0));
            while(references.hasNext()) {
                Reference reference = references.next();
                refs.println(reference.getFromAddress()+"\t"+reference.getToAddress()+"\t"+reference.getReferenceType());
            }
        }
        decompiler.dispose();
    }
}
