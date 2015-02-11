package com.nscc.movietrailer;

import java.util.ArrayList;
import java.util.List;

import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemLongClickListener;
import android.widget.ListView;

import com.example.movietrailer.R;
import com.nscc.movietrailer.Movie;
import com.nscc.movietrailer.MySQLiteHelper;
import com.nscc.movietrailer.adapters.CustomBaseAdapter;
 
public class ActivityMain extends Activity implements
        OnItemClickListener {
 
    public static final String[] movieTitle = new String[] { 
    	"The Avengers",
        "Jumanji", 
        "Step Brothers",
        "Titanic",
        "The Hunger Games",
        "The Lego Movie"
    };
 
    public static final String[] movieDesc = new String[] {
        "Earth's mightiest heroes must come together and learn to fight as a team if they are to stop the mischievous Loki and his alien army from enslaving humanity.",
        "A mysterious game transports its players to the jungles of Jumanji! Thrilling effects!",
        "Brennan Huff and Dale Doback are both about 40 when Brennan's mom and Dale's dad marry. The sons still live with the parents so they must now share a room. Initial antipathy threatens the household's peace and the parents' relationship.",
        "An old lady who claims to be a survivor of the Titanic tells her story to an eager group of tresure hunters, who are insearch of a rare diamond in the Titanic's wreckage.",
        "Every year, the Capitol of the nation of Panem forces each of its twelve districts to send a teenage boy and girl to compete in the Hunger Games. Katniss Everdeen volunteers in her sister's place, and must make impossible choices in the arena.",
        "The first-ever full-length theatrical LEGO movie follows Emmet, an ordinary, rules-following, perfectly average LEGO minifigure who is mistakenly identified as the most extraordinary person and the key to saving the world."
   };
 
    public static final Integer[] movieImage = { 
    		R.drawable.the_avengers,
            R.drawable.jumanji,
            R.drawable.step_brothers,
            R.drawable.titanic,
            R.drawable.the_hunger_games, 
            R.drawable.the_lego_movie
    };
    
    public static final String[] movieClip = { 
		"the_avengers",
		"jumanji",
        "step_brothers",
        "titanic",
        "the_hunger_games",
        "the_lego_movie" 
    };
    
    public static final float[] movieRating = {
    	(float)0,
    	(float)0,
    	(float)0,
    	(float)0,
    	(float)0,
    	(float)0
    };
 
    ListView listView;
    List<MovieItems> rowItems;
    ArrayList<String> addItems;
    
    MySQLiteHelper db = new MySQLiteHelper(this);
 
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
       	super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // The trailers that can be added
        addItems = new ArrayList<String>();
        addItems.add("avatar");
        addItems.add("the_dark_knight");
              
        // Reset the database to drop old table
        db.resetDatabase();
        
        // Add movies from list into table
        for (int i=0; i<movieTitle.length; i++){
        	db.addMovie(new Movie(movieTitle[i],movieDesc[i], movieImage[i], movieClip[i], movieRating[i]));
        }
       
        updateDisplay();
    }
    
    
    public void updateDisplay(){
    	

        // Get information from the database
        List<Movie> movieList = db.getAllMovies();
        rowItems = new ArrayList<MovieItems>();
        
        // Add movies to display list
        for(int i=0; i<movieList.size();i++){
        	Movie movie = movieList.get(i);
        	MovieItems item = new MovieItems(movie.getId(),movie.getImage(),movie.getTitle(),movie.getDesc());
        	rowItems.add(item); 
        }        

        // Display lists
        listView = (ListView) findViewById(R.id.list);
        CustomBaseAdapter adapter = new CustomBaseAdapter(this, rowItems);
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(this);
        listView.setOnItemLongClickListener(new OnItemLongClickListener() {
        	
        	// Prompt to delete on long click
        	@Override
            public boolean onItemLongClick(AdapterView<?> parent, View view,
                int position, long id){
        		
        		MovieItems item = rowItems.get(position);
        		int movieId = item.getMovieId();
        		Movie selectedMovie = db.getMovie(movieId);
            	
            	AlertDialog diaBox = AskOption(selectedMovie);
            	diaBox.show();
            	
            	return true;
            	
        	}
        });
    }
 
    // Go to trailer on click
    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position,
            long id) {
    	
		MovieItems item = rowItems.get(position);
		int movieId = item.getMovieId();
		Movie selectedMovie = db.getMovie(movieId);
    	
		Intent i=new Intent(ActivityMain.this, ActivityMoviePlayer.class);
		
		i.putExtra("id",selectedMovie.getId());
		i.putExtra("clip",selectedMovie.getClip());
		i.putExtra("desc", selectedMovie.getDesc());
		i.putExtra("rating", selectedMovie.getRating());

	    startActivity(i);

    }    
    
    // Prompt for delete
    private AlertDialog AskOption(final Movie selectedMovie)
    {
       AlertDialog myQuittingDialogBox =new AlertDialog.Builder(this) 
           
           .setTitle("Delete") 
           .setMessage("Do you want to delete " + selectedMovie.getTitle() + "?") 
          
           .setPositiveButton("Delete", new DialogInterface.OnClickListener() {

               public void onClick(DialogInterface dialog, int whichButton) { 
            	   
            	   //add movie to addlist before deleting
            	   addItems.add(selectedMovie.getClip());
          	   
            	   db.deleteMovie(selectedMovie);
            	   updateDisplay();            	               	   
                   dialog.dismiss();
               }   

           })

           .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
               public void onClick(DialogInterface dialog, int which) {

                   dialog.dismiss();

               }
           })
           .create();
           return myQuittingDialogBox;

       }
    
    // Menu inflater
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.options, menu);
        return true;
    }
    
    // Options from menu
    public boolean onOptionsItemSelected(MenuItem item) {
        // Respond to menu item selection
    	switch (item.getItemId()) {
    	
        // If add is selected, pass add list and start activity
    	case R.id.add:
        	Intent i=new Intent(ActivityMain.this, ActivityAdd.class);    		
    		i.putStringArrayListExtra("list", addItems);    		
	        startActivityForResult(i,0);
	        return true;
        default:
        	return super.onOptionsItemSelected(item);
    	}   	
    }
    
    // Check when coming back from add activity for updated list
    protected void onActivityResult(int requestCode,int resultCode,Intent getI) 
    {
         if (requestCode == 0) 
         {
             if (resultCode == Activity.RESULT_OK ) 
             {     
            	 // Get list and update display
                 addItems = getI.getStringArrayListExtra("list");
                 updateDisplay();                   
                 
             }
         }
         
     }
}
