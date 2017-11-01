/**
 * It is okay to use ArrayList class but you are not allowed to use any other
 * predefined class supplied by Java.
 */
import java.util.ArrayList;

public class CompressDecompress
{
	/**
	 * Get a string representing a Huffman tree where its root node is root
	 * @param root the root node of a Huffman tree
	 * @return a string representing a Huffman tree
	 */
	public static String getTreeString(final BinaryNodeInterface<Character> root)
	{
		// TO DO
		if (root == null) {
			return "";
		}
		StringBuilder builder = new StringBuilder();
		getTrees(root, builder, "");
		return builder.toString();
		// StringBuilder builder = new StringBuilder();
		// getTreeString2(root, builder, "");
		// // prints out the string from String Builder.
		// return builder.toString();

		//return "";	// Do not forget to change this line!!!
	}

	public static void getTrees(final BinaryNodeInterface<Character> currentRoot, StringBuilder build, String currentPlace) {
		if (currentRoot != null) {
			if (currentRoot.isLeaf() == true) {
				build.append(currentPlace + "L" + currentRoot.getData());
			}
			else {
				build.append(currentPlace + "I");
			}
			getTrees(currentRoot.getLeftChild(), build, currentPlace);
			getTrees(currentRoot.getRightChild(), build, currentPlace);
		}
	}

	public static void getTreeString2(final BinaryNodeInterface<Character> currentRoot, String currentPlace, ArrayList<String> str, ArrayList<Character> chara) {
		if (currentRoot != null) {
			if (currentRoot.isLeaf() == true) {
				chara.add(currentRoot.getData());
				str.add(currentPlace);
			}
			getTreeString2(currentRoot.getLeftChild(), currentPlace + "0", str, chara);
			getTreeString2(currentRoot.getRightChild(), currentPlace + "1", str, chara);
		}
	}

	/**
	 * Compress the message using Huffman tree represented by treeString
	 * @param root the root node of a Huffman tree
	 * @param message the message to be compressed
	 * @return a string representing compressed message.
	 */
	public static String compress(final BinaryNodeInterface<Character> root, final String message)
	{
		// TO DO
		if (root == null) {
			return "";
		}
		StringBuilder builder = new StringBuilder();
		ArrayList<String> str = new ArrayList<String>();
		ArrayList<Character> chara = new ArrayList<Character>();
		getTreeString2(root, "", str, chara);
		for (int i = 0; i < message.length(); i++) {
			builder.append(str.get(chara.indexOf(message.charAt(i))));
		}
		// prints out the string from String Builder.
		return builder.toString();


		// return "";	// Do not forget to change this line!!!
	}

	/**
	 * Decompress the message using Huffman tree represented by treeString
	 * @param treeString the string represents the Huffman tree of the
	 * compressed message
	 * @param message the compressed message to be decompressed
	 * @return a string representing decompressed message
	 */
	public static String decompress(final String treeString, final String message)
	{
		// TO DO
		// if (treeString == null || treeString == "") {
		// 	return "";
		// }
		StringBuilder builder = new StringBuilder();
		// stores all characters in the tree string
		ArrayList<Character> chars = new ArrayList<Character>();
		for (int i = 0; i < treeString.length(); i++) {
			chars.add(treeString.charAt(i));
		}
		BinaryNodeInterface<Character> start = createTree(chars);
		BinaryNodeInterface<Character> root = start;
		for (int i = 0; i < message.length(); i++) {
			if (message.charAt(i) == '0') {
				root = root.getLeftChild();
			}
			else if (message.charAt(i) == '1') {
				root = root.getRightChild();
			}
			if (root.isLeaf()) {
				builder.append(root.getData());
				root = start;
			}
		}
		return builder.toString();
		// return "";	// Do not forget to change this line!!!
	}

	public static BinaryNode<Character> createTree(ArrayList<Character> charss) {
		if (charss.isEmpty()) {
			return null;
		}
		char counter = charss.remove(0);
		if (counter == 'L') {
			return new BinaryNode<Character>(charss.remove(0), null, null);
		}
		else {
			return new BinaryNode<Character>(null, createTree(charss), createTree(charss));
		}
	}
}
