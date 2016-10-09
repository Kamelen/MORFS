package morfsengine

import morfsengine.Dataset._

/**
 * Created by epenerk on 8/21/16.
 */

object DataLoader {
  def getDatasetFromCsvFile(filepath : String) : Dataset = {
    val file = io.Source.fromFile(filepath)
    val lines = file.getLines()
    val header = lines.take(1).next().split(",").map(_.trim).toList

    val builder = Dataset.builder().labeled(header).whereTargetsAre(Seq(1))
    //foreach line get the instance from that line and return a list of lines
    appendInstances(builder,lines).build()
}
  def appendInstances(builder: DatasetBuilder, lines: Iterator[String]): DatasetBuilder = {
    lines.hasNext match {
      case true => appendInstances(getInstanceFromLine(lines.next()) :: builder, lines)
      case false => builder
    }
  }

  def getInstanceFromLine(line: String): Instance = {
    val cols = line.split(",").map(_.trim)
    Instance(cols.map(col => col.toDouble).toVector)
  }
}

class DataLoader {
  
}
