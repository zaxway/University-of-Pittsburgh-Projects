import java.lang.*;

public class plaintextSoftware {
  public static void main(String[] args) {
    RTFEditorKit rtfParser = new RTFEditorKit();
    Document document = rtfParser.createDefaultDocument();
    rtfParser.read(new ByteArrayInputStream(rtfBytes), document, 0);
    String text = document.getText(0, document.getLength());
  }
}
