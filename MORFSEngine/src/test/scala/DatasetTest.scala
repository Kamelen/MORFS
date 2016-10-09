package morfsengine

import  org.scalatest.{Matchers, PropSpec}
import org.scalatest._

class DatasetTest extends FlatSpec with Matchers{

  trait exampleData {
    val exampleInstance = Instance(Vector(5, 5))
    val dataset = Dataset.builder() labeled List("lable1", "lable2") whereTargetsAre Seq(2) addInstance  exampleInstance addInstance  exampleInstance build()
  }


  "A Dataset" should "be countable" in new exampleData {
    dataset.instances.size should be(2)
    println(dataset)
  }
}
