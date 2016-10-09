/**
  * Created by epenerk on 10/4/16.
  */
package morfsengine

import  org.scalatest.{Matchers, PropSpec}
import org.scalatest._

class DataLoaderTest extends FlatSpec with Matchers{

  trait testFiles {
    val test1 = "/git/github/MORFS/MORFSEngine/src/test/scala/small.csv"
    val test2 = "/git/github/MORFS/MORFSEngine/src/test/scala/large.csv"
  }

   behavior of "Dataloader"

  it should "be able to parse small csv file and get a dataset" in new testFiles {
    val d = DataLoader.getDatasetFromCsvFile(test1)
    assert(d.instances.size === 3)
  }

  it should "be able to parse large csv file and get a dataset" in new testFiles {
    val d = DataLoader.getDatasetFromCsvFile(test2)
    assert(d.instances.size === 1000)
  }
}

