package com.nscc.movietrailer;

public class Movie {
		 
	    private int id;
	    private String title;
	    private String desc;
	    private int image;
	    private String clip;
	    private float rating;
	 
	    public Movie(){}
	 
	    public Movie(String title, String desc, int image, String clip, float rating) {
	        super();
	        this.title = title;
	        this.desc = desc;
	        this.image = image;
	        this.clip = clip;
	        this.rating = rating;
	    }
	    
	    // Getters/Setters
	    @Override
	    public String toString() {
	        return "Movie [id=" + id + ", title=" + title + ", desc=" + desc
	        		+ ", image=" + image + ", clip=" + clip + ", rating=" + rating
	        		+ "]";
	    }

		public int getId() {
			return id;
		}

		public void setId(int id) {
			this.id = id;
		}

		public String getTitle() {
			return title;
		}

		public void setTitle(String title) {
			this.title = title;
		}

		public String getDesc() {
			return desc;
		}

		public void setDesc(String desc) {
			this.desc = desc;
		}

		public int getImage() {
			return image;
		}

		public void setImage(int image) {
			this.image = image;
		}

		public String getClip() {
			return clip;
		}

		public void setClip(String clip) {
			this.clip = clip;
		}

		public float getRating() {
			return rating;
		}

		public void setRating(float rating) {
			this.rating = rating;
		}
}
