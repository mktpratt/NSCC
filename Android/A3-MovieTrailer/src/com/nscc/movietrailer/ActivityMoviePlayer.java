package com.nscc.movietrailer;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.VideoView;
import android.widget.TextView;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.RatingBar;
import android.widget.RatingBar.OnRatingBarChangeListener;

import com.example.movietrailer.R;
import com.nscc.movietrailer.Movie;
import com.nscc.movietrailer.MySQLiteHelper;

public class ActivityMoviePlayer extends Activity{
	
	private VideoView mVideoView;
	private RatingBar ratingBar;
	private TextView mDescription;
	private ImageView mIcon;
	
	MySQLiteHelper db = new MySQLiteHelper(this);
	
	private ImageButton mPlay;
	private ImageButton mPause;
	private ImageButton mReset;
	private ImageButton mStop;

	float rating;
	int id;
	int pos = 0;
	
	@Override
	protected void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
		outState.putInt("pos", mVideoView.getCurrentPosition());		
	}

	
	@Override
    public void onCreate(Bundle savedInstanceState) {
       	super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_movie);
        
        mDescription = (TextView) findViewById(R.id.textViewDesc);
        mIcon = (ImageView) findViewById(R.id.imageViewIcon);
        
        // Check for saved state of video
        if(savedInstanceState != null)
        {
            pos = savedInstanceState.getInt("pos");
        }
        
        addListenerOnRatingBar();
        
        // Get intent from main activity
        Intent getI=getIntent();
        id = getI.getIntExtra("id", 0);
        
        String clip = getI.getStringExtra("clip");
        rating = getI.getFloatExtra("rating", 0);
        String desc = getI.getStringExtra("desc");
        
        ratingBar.setRating(rating);
        
        
        // Get the movie location and start video player
        String videoUrl = "android.resource://" + getPackageName() + "/" + getResources().getIdentifier(clip, "raw", getPackageName());      
        Uri vidPath = Uri.parse(videoUrl);
        mVideoView = (VideoView) findViewById(R.id.surface_view);
        mVideoView.setVideoURI(vidPath);
        mVideoView.requestFocus();
        mVideoView.seekTo(pos);
        mVideoView.start();
        
        mPlay = (ImageButton) findViewById(R.id.play);
		mPause = (ImageButton) findViewById(R.id.pause);
		mReset = (ImageButton) findViewById(R.id.reset);
		mStop = (ImageButton) findViewById(R.id.stop);
		
		mDescription.setText(desc);
		String iconUrl = "android.resource://" + getPackageName() + "/" + getResources().getIdentifier(clip, "drawable", getPackageName());
		Uri iconPath = Uri.parse(iconUrl);
		mIcon.setImageURI(iconPath);

		// Start button
		mPlay.setOnClickListener(new OnClickListener() {
			public void onClick(View view) {
				mVideoView.start();
			}
		});
		
		// Pause button
		mPause.setOnClickListener(new OnClickListener() {
			public void onClick(View view) {
				if (mVideoView != null) {
					mVideoView.pause();
				}
			}
		});
		
		// Reset button
		mReset.setOnClickListener(new OnClickListener() {
			public void onClick(View view) {
				if (mVideoView != null) {
					mVideoView.seekTo(0);
				}
			}
		});
		
		// Stop button closes video player
		mStop.setOnClickListener(new OnClickListener() {
			public void onClick(View view) {
				if (mVideoView != null) {
					mVideoView.stopPlayback();
					finish();
				}
			}
		});
	} // End method onCreate
	
	public void addListenerOnRatingBar() {
		 
		ratingBar = (RatingBar) findViewById(R.id.ratingBar);
	 
		// If rating value is changed
		ratingBar.setOnRatingBarChangeListener(new OnRatingBarChangeListener() {
			public void onRatingChanged(RatingBar ratingBar, float rating,
				boolean fromUser) {
				
				// Get the rating
				rating = ratingBar.getRating();
				
				// Get the movie
				Movie selectedMovie = db.getMovie(id);
				
				// Change the rating in the movie
				selectedMovie.setRating(rating);
				
				// Update the open in the database
				db.updateMovie(selectedMovie);

	 
			}
		});
	  } // End method addListenerOnRatingBar
}
