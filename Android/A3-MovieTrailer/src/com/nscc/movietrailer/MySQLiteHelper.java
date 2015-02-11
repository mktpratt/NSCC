package com.nscc.movietrailer;

import java.util.LinkedList;
import java.util.List;
 

 
import com.nscc.movietrailer.Movie;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

 
public class MySQLiteHelper extends SQLiteOpenHelper {
 
    // Database Version
    private static final int DATABASE_VERSION = 1;
    // Database Name
    private static final String DATABASE_NAME = "MikeMovieDB";
 
    public MySQLiteHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);  
    }
 
    @Override
    public void onCreate(SQLiteDatabase db) {
    	   	
        // SQL statement to create movie table
        String CREATE_MOVIE_TABLE = "CREATE TABLE movie ( " +
                "id INTEGER PRIMARY KEY AUTOINCREMENT, " + 
                "title TEXT, "+
                "desc TEXT, "+
                "image INTEGER, "+
                "clip TEXT, "+
                "rating FLOAT )";
 
        // create movie table
        db.execSQL(CREATE_MOVIE_TABLE);
    }
 
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Drop older movie table if existed
        db.execSQL("DROP TABLE IF EXISTS movie");
 
        // Create fresh movies movie
        this.onCreate(db);
    }
    
    // Movies table name
    private static final String TABLE_MOVIE = "movie";
 
    // Movies Table Columns names
    private static final String KEY_ID = "id";
    private static final String KEY_TITLE = "title";
    public static final String KEY_DESC = "desc";
    public static final String KEY_IMAGE = "image";
    public static final String KEY_CLIP = "clip"; 
    public static final String KEY_RATING = "rating";
 
    private static final String[] COLUMNS = { KEY_ID,KEY_TITLE,KEY_DESC,KEY_IMAGE,KEY_CLIP,KEY_RATING };
 
    public void addMovie(Movie movie){
        Log.d("addMovie", movie.toString());
        // Get reference to writable DB
        SQLiteDatabase db = this.getWritableDatabase();
 
        // Create ContentValues to add key "column"/value
        ContentValues values = new ContentValues();
        values.put(KEY_TITLE, movie.getTitle()); // get title 
        values.put(KEY_DESC, movie.getDesc()); // get desc
        values.put(KEY_IMAGE, movie.getImage());
        values.put(KEY_CLIP, movie.getClip());
        values.put(KEY_RATING,movie.getRating());
 
        // Insert movie
        db.insert(TABLE_MOVIE, // table
                null, //nullColumnHack
                values); // key/value -> keys = column names/ values = column values
 
        // Close db
        db.close(); 
    }
 
    // Get a movie
    public Movie getMovie(int id){
 
        // Get reference to readable DB
        SQLiteDatabase db = this.getReadableDatabase();
 
        // Build query
        Cursor cursor = 
                db.query(TABLE_MOVIE, // a. table
                COLUMNS, // b. column names
                " id = ?", // c. selections 
                new String[] { String.valueOf(id) }, // d. selections args
                null, // e. group by
                null, // f. having
                null, // g. order by
                null); // h. limit
 
        // If we find results get the first one
        if (cursor != null)
            cursor.moveToFirst();
 
        // Build movie object
        Movie movie = new Movie();
        movie.setId(Integer.parseInt(cursor.getString(0)));
        movie.setTitle(cursor.getString(1));
        movie.setDesc(cursor.getString(2));
        movie.setImage(cursor.getInt(3));
        movie.setClip(cursor.getString(4));
        movie.setRating(cursor.getFloat(5));
 
        Log.d("getMovie("+id+")", movie.toString());
        
        db.close();
 
        // Return movie
        return movie;
    }
 
    // Get All Movies
    public List<Movie> getAllMovies() {
        List<Movie> movies = new LinkedList<Movie>();
 
        // Build the query
        String query = "SELECT * FROM " + TABLE_MOVIE;
 
        // Get reference to writable DB
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor cursor = db.rawQuery(query, null);
 
        // Go over each row, build movie and add it to list
        Movie movie = null;
        if (cursor.moveToFirst()) {
            do {
                movie = new Movie();
                movie.setId(Integer.parseInt(cursor.getString(0)));
                movie.setTitle(cursor.getString(1));
                movie.setDesc(cursor.getString(2));
                movie.setImage(cursor.getInt(3));
                movie.setClip(cursor.getString(4));
                movie.setRating(cursor.getFloat(5));
 
                // Add movie to movies
                movies.add(movie);
            } while (cursor.moveToNext());
        }
 
        Log.d("getAllMovies()", movies.toString());
        
        db.close();
 
        // return movies
        return movies;
    }
 
     // Updating single movie
    public int updateMovie(Movie movie) {
 
        // Get reference to writable DB
        SQLiteDatabase db = this.getWritableDatabase();
 
        // Create ContentValues to add key "column"/value
        ContentValues values = new ContentValues();
        values.put(KEY_TITLE, movie.getTitle()); // get title 
        values.put(KEY_DESC, movie.getDesc()); // get desc
        values.put(KEY_IMAGE, movie.getImage());
        values.put(KEY_CLIP, movie.getClip());
        values.put(KEY_RATING,movie.getRating());
 
        // Updating row
        int i = db.update(TABLE_MOVIE, //table
                values, // column/value
                KEY_ID+" = ?", // selections
                new String[] { String.valueOf(movie.getId()) }); //selection args
 
        // Close
        db.close();
 
        return i;
 
    }
 
    // Deleting single movie
    public void deleteMovie(Movie movie) {
 
        // Get reference to writable DB
        SQLiteDatabase db = this.getWritableDatabase();
 
        // Delete
        db.delete(TABLE_MOVIE,
                KEY_ID+" = ?",
                new String[] { String.valueOf(movie.getId()) });
 
        // Close
        db.close();
 
        Log.d("deleteMovie", movie.toString());
 
    }
    
    public void resetDatabase() {
    	
        // Get reference to writable DB
        SQLiteDatabase db = this.getWritableDatabase();
        
        // Drop older movie table if existed
        db.execSQL("DROP TABLE IF EXISTS movie");
        
        // Create fresh movies movie
        this.onCreate(db);

    }
}

 
