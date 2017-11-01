
public class BNHelper
{
	/**
	 * Return the reference to the left most node of
	 * a subtree rooted at rootNode.
	 *
	 * @param rootNode  A root node of a subtree
	 * @return reference to the left most node
	 */
	public static <T> BinaryNodeInterface<T> getLeftMostNode(BinaryNodeInterface<T> rootNode)
	{
		// TO DO
		if (rootNode == null) {
			return null;
		}
		if(!rootNode.hasLeftChild()) {
			return rootNode;
		}
		return getLeftMostNode(rootNode.getLeftChild());
	}

	/**
	 * Return the reference to the right most node of
	 * a subtree rooted at rootNode.
	 *
	 * @param rootNode  A root node of a subtree
	 * @return reference to the right most node
	 */
	public static <T> BinaryNodeInterface<T> getRightMostNode(BinaryNodeInterface<T> rootNode)
	{
		// TO DO
		// BinaryNodeInterface<T> root = new BinaryNodeInterface<T>();
		// while(rootNode.hasRightChild()) {
		// 	root = rootNode.getData();
		// }
		// return root;
		if (rootNode == null) {
			return null;
		}
		if(!rootNode.hasRightChild()) {
			return rootNode;
		}
		return getRightMostNode(rootNode.getRightChild());
	}

	/**
	 * Get the array of data associated with inorder traversal
	 * of a subtree rooted at rootNode. For this traversal,
	 * visit all nodes in the rootNode's left subtree first, then rootNode,
	 * and then all nodes in the rootNode's right subtree.
	 *
	 * @param rootNode  A root node of a subtree
	 * @return an array
	 */
	public static <T> T[] getArrayInorderLeftFirst(BinaryNodeInterface<T> rootNode)
	{
		@SuppressWarnings("unchecked")
		T[] result = (T[]) new Object[rootNode.getNumberOfNodes()];

		// TO DO
		// if(rootNode != null) {
		// 	inorderTraverse(rootNode.getRightChild());
		// 	System.out.println(rootNode.getData());
		// 	inorderTraverse(rootNode.getLeftChild());
		// }

		return result;
	}

	// public static void inorderTraverse(BinaryNodeInterface<T> rootNode)
	// {
	// 	inorderTraverse(rootNode);
	// }

	/**
	 * Get the array of data associated with inorder traversal
	 * of a subtree rooted at rootNode. For this traversal,
	 * visit all nodes in the rootNode's right subtree first, then rootNode,
	 * and then all nodes in the rootNode's left subtree.
	 *
	 * @param rootNode  A root node of a subtree
	 * @return an array
	 */
	public static <T> T[] getArrayInorderRightFirst(BinaryNodeInterface<T> rootNode)
	{
		@SuppressWarnings("unchecked")
		T[] result = (T[]) new Object[rootNode.getNumberOfNodes()];

		// TO DO

		return result;
	}

	/**
	 * Get the reference to a node containing aData from a subtree
	 * rooted at rootNode.
	 *
	 * @param rootNode  A root node of a subtree
	 * @param aData  The data to search for
	 * @return the reference to a node containing aData. If no such data
	 *         is found, return null.
	 */
	public static <T> BinaryNodeInterface<T> getReferenceTo(BinaryNodeInterface<T> rootNode, T aData)
	{
		// TO DO
		return null;
	}
}
