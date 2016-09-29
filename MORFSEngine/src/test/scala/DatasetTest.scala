package morfsengine

import  org.scalatest.{Matchers, PropSpec}
import org.scalatest._
import DataLoader.getDatasetFromCsvFile

class DatasetTest extends FlatSpec with Matchers{

  trait exampleData {
    val exampleFeature = new Feature("featureName", "featureval")
    val exampleSample = new Sample(Vector(exampleFeature), Vector(exampleFeature))
    val exampleDataset = List(exampleSample,exampleSample)
  }


  "A Dataset" should "be countable" in new exampleData {
    exampleDataset.size should be(2)
    println(exampleDataset.mkString)
  }
}
