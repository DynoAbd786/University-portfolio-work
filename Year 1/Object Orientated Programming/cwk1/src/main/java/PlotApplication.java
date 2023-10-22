import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;
import java.io.IOException;

/**
 * JavaFX application to plot elevations of a GPS track, for
 * the Advanced task of COMP1721 Coursework 1.
 *
 * @author Muhammad Kashif-Khan
 */
public class PlotApplication extends Application 
{
  @Override
  public void start(Stage stage) throws Exception
  {
    // Initialise new track and load points onto it
    String filename = getParameters().getRaw().get(0);
    Track dataToPlot = new Track();

    // Error checking if any exceptions appear while reading/calculating points
    try 
    {
      dataToPlot.readFile(filename);
      dataToPlot.totalDistance();
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

    // Define the x and y axes
    final NumberAxis xAxis = new NumberAxis();
    final NumberAxis yAxis = new NumberAxis();
    xAxis.setLabel("Distance (metres)");
    yAxis.setLabel("Elevation (metres)");

    // Create the line chart
    final LineChart<Number, Number> lineChart = new LineChart<>(xAxis, yAxis);
    lineChart.setTitle("Plot of Distance against Elevation");

    XYChart.Series<Number, Number> series = new XYChart.Series<>();
    series.setName(filename.replace("data/", ""));

    // Plot Co-ordinates
    Double distance = 0.0;

    for (int i = 0; i < dataToPlot.size(); i++)
    {
      Point pointFromData = dataToPlot.get(i);
      Double elevation = pointFromData.getElevation();
      
      if (i == 0)
      {
        series.getData().add(new XYChart.Data<>(distance, elevation));
      }
      else
      {
        Point previousPointFromData = dataToPlot.get(i - 1);
        distance = distance + Point.greatCircleDistance(previousPointFromData, pointFromData);

        series.getData().add(new XYChart.Data<>(distance, elevation));
      }
    }

    // Add the data series to the chart
    lineChart.getData().add(series);

    // Create the scene and show the chart
    Scene scene = new Scene(lineChart, 800, 600);
    stage.setScene(scene);
    stage.show();
  }


  public static void main(String[] args) {
    // Error checking if file has been supplied/correct arguements given
    if (args.length != 1)
    {
      System.err.println("Usage: java ElevationPlot filename.csv");
      System.exit(0);
    }

    launch(args);
  }
}
