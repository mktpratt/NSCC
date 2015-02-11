package com.nscc.movietrailer;

public class MovieItems {
	private int movieId;
    private int imageId;
    private String title;
    private String desc;
 
    public MovieItems(int movieId, int imageId, String title, String desc) {
    	this.movieId = movieId;
        this.imageId = imageId;
        this.title = title;
        this.desc = desc;
    }
    public int getImageId() {
        return imageId;
    }
    public void setImageId(int imageId) {
        this.imageId = imageId;
    }
    public String getDesc() {
        return desc;
    }
    public void setDesc(String desc) {
        this.desc = desc;
    }
    public String getTitle() {
        return title;
    }
    public void setTitle(String title) {
        this.title = title;
    }
    
    
    public int getMovieId() {
		return movieId;
	}
	public void setMovieId(int movieId) {
		this.movieId = movieId;
	}
	@Override
    public String toString() {
        return title + "\n" + desc;
    }
}
