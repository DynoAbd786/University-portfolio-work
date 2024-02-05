import java.time.ZonedDateTime;

import static java.lang.Math.abs;
import static java.lang.Math.atan2;
import static java.lang.Math.cos;
import static java.lang.Math.sin;
import static java.lang.Math.sqrt;
import static java.lang.Math.toRadians;


/**
 * Represents a point in space and time, recorded by a GPS sensor.
 *
 * @author Nick Efford & Muhammad Kashif-Khan
 */
public class Point {
  // Constants useful for bounds checking, etc
  private static final double MIN_LONGITUDE = -180.0;
  private static final double MAX_LONGITUDE = 180.0;
  private static final double MIN_LATITUDE = -90.0;
  private static final double MAX_LATITUDE = 90.0;
  private static final double MEAN_EARTH_RADIUS = 6.371009e+6;

  // Variables for Point class
  private ZonedDateTime time;
  private double latitude;
  private double longitude;
  private double elevation;

  // Stub for constructor
  public Point()
  {
    this(null, 0, 0, 0);
  }

  // Constructor for Point class
  public Point (ZonedDateTime t, double lon, double lat, double elev)
  {
    setTime(t);
    setLatitude(lat);
    setLongitude(lon);
    setElevation(elev);
  }


  // Gets the time using the time stamp within the point class
  public ZonedDateTime getTime()
  {
    return time;
  }

  // Sets the time using the time stamp within the point class
  private void setTime(ZonedDateTime t)
  {
    time = t;
  }


  // Gets the latitude within the point class
  public Double getLatitude()
  {
    return latitude;
  }

  // Sets the latitude within the point class
  private void setLatitude(double lat)
  {
    // Error checking for latitude outside bounds
    if (lat < MIN_LATITUDE || lat > MAX_LATITUDE)
    {
      throw new GPSException("Information for latitude exceeds bounds");
    }

    latitude = lat;
  }


  // Gets the longitude within the point class
  public double getLongitude()
  {
    return longitude;
  }

  // Sets the longitude within the point class
  private void setLongitude(double lon)
  {
    // Error checking for latitude outside bounds
    if (lon < MIN_LONGITUDE || lon > MAX_LONGITUDE)
    {
      throw new GPSException("Information for longitude exceeds bounds");
    }

    longitude = lon;
  }


  // Gets the elevation within the point class
  public double getElevation()
  {
    return elevation;
  }

  // Sets the elevation within the point class
  private void setElevation(double elev)
  {
    elevation = elev;
  }


  // Outputs the correct format for a point
  public String toString()
  {
    String pointRepresentation = String.format("(%.5f, %.5f), %.1f m", longitude, latitude, elevation);
    return pointRepresentation;
  }
  

  // IMPORTANT: Do not alter anything beneath this comment!

  /**
   * Computes the great-circle distance or orthodromic distance between
   * two points on a spherical surface, using Vincenty's formula.
   *
   * @param p First point
   * @param q Second point
   * @return Distance between the points, in metres
   */
  public static double greatCircleDistance(Point p, Point q) {
    double phi1 = toRadians(p.getLatitude());
    double phi2 = toRadians(q.getLatitude());

    double lambda1 = toRadians(p.getLongitude());
    double lambda2 = toRadians(q.getLongitude());
    double delta = abs(lambda1 - lambda2);

    double firstTerm = cos(phi2)*sin(delta);
    double secondTerm = cos(phi1)*sin(phi2) - sin(phi1)*cos(phi2)*cos(delta);
    double top = sqrt(firstTerm*firstTerm + secondTerm*secondTerm);

    double bottom = sin(phi1)*sin(phi2) + cos(phi1)*cos(phi2)*cos(delta);

    return MEAN_EARTH_RADIUS * atan2(top, bottom);
  }
}
