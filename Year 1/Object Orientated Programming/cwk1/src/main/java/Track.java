import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.nio.file.Paths;
import java.time.ZonedDateTime;
import java.time.temporal.ChronoUnit;
/**
 * Represents a point in space and time, recorded by a GPS sensor.
 *
 * @author Muhammad Kashif-Khan
 */
public class Track {
  // Initialise an ArrayList to store point variables
  ArrayList<Point> Points = new ArrayList<Point>();

  // Stub used for initialising Track
  public Track() {  }

  // Initialising Track with given filename
  public Track(String filename)
  {
    // attempt to read given file
    try
    {
      readFile(filename);
    }
    catch (IOException e)
    {
      System.err.println("File does not exist");
    }

  }


  // Reads a file and stores all points from the file to the ArrayList, given the input file exists and all data is given in correct format
  public void readFile(String filename) throws IOException
  {
    // Clear Points array when reading from new file
    Points.clear();

    // Begin reading from file
    String delimiter = ",";
    Scanner input = new Scanner(Paths.get(filename));
    input.nextLine();     // Skip 1st line (1st line includes names of fields)

    // loop until end of file
    while (input.hasNextLine())
    {
      // Read every line and store each comma separated value to an array
      String line = input.nextLine();
      String values[] = line.split(delimiter);

      // Error checking for missing data along line
      if (values.length != 4)
      {
        throw new GPSException("Number of values obtained from file line for 'Point' are not 4");
      }

      // Create new point and store it to ArrayList
      Point pointFromFile = new Point(ZonedDateTime.parse(values[0]), Double.parseDouble(values[1]), Double.parseDouble(values[2]), Double.parseDouble(values[3]));
      add(pointFromFile);
    }
  }


  // Adds a point to the Points ArrayList
  public void add(Point point)
  {
    Points.add(point);
  } 


  // Obtains the point from Points ArrayList, given an index as input
  public Point get(int index)
  {
    // Error checking if index provided is out of bounds
    if (index < 0 || index > Points.size() - 1)
    {
      throw new GPSException("Index out of bounds for Points array");
    }
    return Points.get(index);
  }


  // Obtains the size of the ArrayList
  public int size()
  {
    return Points.size();
  }


  // Obtains the lowest point among the points in the ArrayList
  public Point lowestPoint()
  {
    // Error checking if no points are stored in the Points ArrayList
    if (Points.size() == 0)
    {
      throw new GPSException("No points supplied to find lowest point");
    }

    // Loops throughout the Points ArrayList and checks if the elevation of the currently obtained point is the lowest in the list
    // If not, set the just compared point as the new lowest point
    Point lowestPoint = Points.get(0);

    for (Point pointFromList: Points)
    {
      if (pointFromList.getElevation() < lowestPoint.getElevation())
      {
        lowestPoint = pointFromList;
      }
    }
    return lowestPoint;
  }

  // Obtains the highest point among the points in the ArrayList
  public Point highestPoint()
  {
    // Error checking if no points are stored in the Points ArrayList
    if (Points.size() == 0)
    {
      throw new GPSException("No points supplied to find highest point");
    }

    // Loops throughout the Points ArrayList and checks if the elevation of the currently obtained point is the highest in the list
    // If not, set the just compared point as the new highest point
    Point highestPoint = Points.get(0);

    for (Point pointFromList: Points)
    {
      if (pointFromList.getElevation() > highestPoint.getElevation())
      {
        highestPoint = pointFromList;
      }
    }
    return highestPoint;
  }
  

  // Calculates total distance using all points from Points ArrayList
  public Double totalDistance()
  {
    // Error checking if not enough points are stored in the Points ArrayList (cannot compute total distance)
    if (Points.size() < 2)
    {
      throw new GPSException("Less than 2 points supplied. Cannot calculate total distance");
    }
    
    // Calculate total distance using greatCircleDistance function in point class
    Double totalDistance = 0.0;

    for (int i = 1; i < Points.size(); i++)
    {
      totalDistance = totalDistance + Point.greatCircleDistance(Points.get(i - 1), Points.get(i));
    }

    return totalDistance;
  }


  // Caclulates average speed based on first and last points from Points ArrayList
  public Double averageSpeed()
  {
    // Error checking if not enough points are stored in the Points ArrayList (cannot compute average speed)
    if (Points.size() < 2)
    {
      throw new GPSException("Less than 2 points supplied. Cannot calculate average speed");
    }

    // Calculate difference in time and thus average speed bewteen first and last points
    ZonedDateTime firstPointTime = Points.get(0).getTime();
    ZonedDateTime lastPointTime = Points.get(Points.size() - 1).getTime();
    Long timeDifference = ChronoUnit.SECONDS.between(firstPointTime, lastPointTime);

    Double averageSpeed = totalDistance()/timeDifference;

    return averageSpeed;
  }
}
