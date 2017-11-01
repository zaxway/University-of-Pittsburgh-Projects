
public class SimpleRGB
{
	// TO DO: Instant Variables
	private int width;
	private int height;
	private int [][] red;
	private int [][] blue;
	private int [][] green;

	public SimpleRGB(int aWidth, int aHeight)
	{
		// TO DO: Constructor
		this.width = aWidth;
		this.height = aHeight;
		red = new int [width][height];
		blue = new int [width][height];
		green = new int [width][height];
	}

	/**
	 * Gets the width of this image.
	 * @return the width of this image.
	 */
	public int getWidth()
	{
		// TO DO
		return width;
	}

	/**
	 * Gets the height of this image.
	 * @return the height of this image.
	 */
	public int getHeight()
	{
		// TO DO
		return height;
	}

	/**
	 * Sets the red value at coordinate (x,y) to aRed.
	 * @param x the x coordinate of this image.
	 * @param y the y coordinate of this image.
	 * @param aRed the red value (0 - 255)
	 */
	public void setRed(int x, int y, int aRed)
	{
		// TO DO
		red[x][y] = aRed;
	}

	/**
	 * Sets the green value at coordinate (x,y) to aGreen.
	 * @param x the x coordinate of this image.
	 * @param y the y coordinate of this image.
	 * @param aGreen the green value (0 - 255)
	 */
	public void setGreen(int x, int y, int aGreen)
	{
		// TO DO
		green[x][y] = aGreen;
	}

	/**
	 * Sets the blue value at coordinate (x,y) to aBlue.
	 * @param x the x coordinate of this image.
	 * @param y the y coordinate of this image.
	 * @param aBlue the blue value (0 - 255)
	 */
	public void setBlue(int x, int y, int aBlue)
	{
		// TO DO
		blue[x][y] = aBlue;
	}

	/**
	 * Gets the red value at coordinate (x,y).
	 * @param x the x coordinate of this image.
	 * @param y the y coordinate of this image.
	 * @return the value of red at coordinate (x,y).
	 */
	public int getRed(int x, int y)
	{
		// TO DO
		return red[x][y];
	}

	/**
	 * Gets the green value at coordinate (x,y).
	 * @param x the x coordinate of this image.
	 * @param y the y coordinate of this image.
	 * @return the value of green at coordinate (x,y).
	 */
	public int getGreen(int x, int y)
	{
		// TO DO
		return green[x][y];
	}

	/**
	 * Gets the blue value at coordinate (x,y).
	 * @param x the x coordinate of this image.
	 * @param y the y coordinate of this image.
	 * @return the value of blue at coordinate (x,y).
	 */
	public int getBlue(int x, int y)
	{
		// TO DO
		return blue[x][y];
	}

	/**
	 * Get the NEW image containing only the red color.
	 * The red values of this new image should be exactly
	 * the same as red value of this image. The green and
	 * blue values of this new image should be 0s.
	 * @return the NEW image (SimpleRGB) containing only
	 * the red color of this image.
	 */
	public SimpleRGB getRedImage()
	{
		// TO DO
		SimpleRGB makeredimage = new SimpleRGB(width,height);
		for (int i = 0; i < height; i++) {
			for (int d = 0; d < width; d++) {
				makeredimage.setRed(d,i,getRed(d,i));
				makeredimage.setGreen(d,i,0);
				makeredimage.setBlue(d,i,0);
			}
		}
		return makeredimage;
	}

	/**
	 * Get the NEW image containing only the green color.
	 * The green values of this new image should be exactly
	 * the same as green value of this image. The red and
	 * blue values of this new image should be 0s.
	 * @return the NEW image (SimpleRGB) containing only
	 * the green color of this image.
	 */
	public SimpleRGB getGreenImage()
	{
		// TO DO
		SimpleRGB makeGreenImage = new SimpleRGB(width,height);
		for (int a = 0; a < height; a++) {
			for (int b = 0; b < width; b++) {
				makeGreenImage.setGreen(b,a,getGreen(b,a));
				makeGreenImage.setRed(b,a,0);
				makeGreenImage.setBlue(b,a,0);
			}
		}
		return makeGreenImage;
	}

	/**
	 * Get the NEW image containing only the blue color.
	 * The blue values of this new image should be exactly
	 * the same as blue value of this image. The red and
	 * green values of this new image should be 0s.
	 * @return the NEW image (SimpleRGB) containing only
	 * the blue color of this image.
	 */
	public SimpleRGB getBlueImage()
	{
		// TO DO
		SimpleRGB makeBlueImage = new SimpleRGB(width,height);
		for(int e = 0; e < height; e++) {
			for(int f = 0; f < width; f++) {
				makeBlueImage.setBlue(f,e,getBlue(f,e));
				makeBlueImage.setRed(f,e,0);
				makeBlueImage.setGreen(f,e,0);
			}
		}
		return makeBlueImage;
	}

	/**
	 * Get the NEW image representing the greyscale of this
	 * image. The grey colors are colors that the red, green
	 * and blue value are exactly the same. To convert an RGB
	 * image into a greyscale image, use the following formula
	 * to calculate the new value.
	 *    (0.21 * red) + (0.72 * green) + (0.07 * blue)
	 * For example, suppose the (R,G,B) value of this image at
	 * coordinate (10,20) are (10,100,200), since
	 *    (0.21 * 10) + (0.72 * 100) + (0.07 * 200) = 88
	 * the (R,G,B) value of the new greyscale image at (10,20)
	 * should be (88,88,88).
	 * @return the NEW image representing the greyscale of this
	 * image.
	 */
	public SimpleRGB getGreyImage()
	{
		// TO DO
		SimpleRGB makeGrayImage = new SimpleRGB(width,height);
		for (int w = 0; w < height; w++) {
			for (int v = 0; v < width; v++) {
				int graycolor = (int) ((0.21 * getRed(v,w)) + (0.72 * getGreen(v,w)) + (0.07 * getBlue(v,w)));
				makeGrayImage.setRed(v,w,graycolor);
				makeGrayImage.setBlue(v,w,graycolor);
				makeGrayImage.setGreen(v,w,graycolor);
			}
		}
		return makeGrayImage;
	}
}
