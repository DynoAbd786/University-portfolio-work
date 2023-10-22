import java.io.IOException;

/**
 * Program to provide information on a GPS track stored in a file.
 *
 * @author Muhammad Kashif-Khan
 */
public class TrackInfo {
  public static void main(String[] args) {
    // Error checking if file has been supplied/correct arguements given
    if (args.length != 1)
    {
      System.err.println("Usage: java TrackInfo filename.csv");
      System.exit(0);
    }

    // Initialise new track and load points onto it
    Track trackInfo = new Track();
    String filename = args[0];

    // Error checking if any exceptions appear while reading/calculating points
    try 
    {
      trackInfo.readFile(filename);
      trackInfo.size();
      trackInfo.lowestPoint();
      trackInfo.highestPoint();
      trackInfo.totalDistance();
      trackInfo.averageSpeed();
    } 
    catch (IOException e) 
    {
      System.err.println("Error reading file");
      System.exit(1);
    }
    catch (GPSException gpsErr)
    {
      System.err.println("Problem with GPS information supplied/calculated: "+ gpsErr.getMessage());
      System.exit(2);
    }

    // Obtain information about the track and output it in a sensible format
    int numberOfPoints = trackInfo.size();
    Point lowestPoint = trackInfo.lowestPoint();
    Point highestPoint = trackInfo.highestPoint();
    double totalDistanceKm = trackInfo.totalDistance()/1000.0;
    double averageSpeedMpS = trackInfo.averageSpeed();

    System.out.printf("%d points in track\n", numberOfPoints);
    System.out.printf("Lowest point is %s\n", lowestPoint.toString());
    System.out.printf("Highest point is %s\n", highestPoint.toString());
    System.out.printf("Total distance = %.3f Km\n", totalDistanceKm);
    System.out.printf("Average speed = %.3f m/s\n", averageSpeedMpS);
  }
}
