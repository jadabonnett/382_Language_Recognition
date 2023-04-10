import org.antlr.v4.runtime.*;
import java.io.File;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws Exception {
        File myObj = new File("src/testFail.txt");
        Scanner myReader = new Scanner(myObj);
        while (myReader.hasNextLine()) {
            String data = myReader.nextLine();
            System.out.println(data);
            CharStream input = CharStreams.fromString(data);
            ExprLexer lexer = new ExprLexer(input);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            ExprParser parser = new ExprParser(tokens);
            //try {
                parser.s(); // parse the input stream!
//                System.out.printf("This is valid\n");
//            }catch(Exception ex){
//                System.out.printf("This is not valid\n");
//            }
        }
    };
}
