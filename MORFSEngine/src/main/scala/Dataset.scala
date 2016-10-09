package morfsengine

/**
 * Created by epenerk on 8/21/16.
 */

// label, lable, lable, lable = lables/attributeNames
// value, value, value, value = instance
// value, value, value, value
// value, value, value, value
// value, value, value, value
// value, value, value, value

//DSL builder like pattern for creating a dataset
//construct using lables List("","","") with targets Seq(1,2) loadInstances(???)
//loadInstances should be able to either take a pure list of instances or a filepath to a csv file
object Dataset {
  def builder(): DatasetBuilder = {
    new DatasetBuilder
  }
}
case class Dataset(lables: List[String], targets: Seq[Int],instances: List[Instance]) {

  override def toString: String = {
    val sb = new StringBuilder
    val lablesWithTargets = lables.zipWithIndex.map {
      case ( element, index) if targets.contains(index) => s"t($element)"
      case ( element, index) => element
    }
    sb ++= "Labels " ++= lablesWithTargets.mkString("(",", ",")") ++= System.lineSeparator()
    instances.foreach(i => sb ++= "Instance " ++= i.values.mkString("(",", ",")") ++= System.lineSeparator() )

    sb.toString()
  }
}

case class Instance(values : Vector[Double])

class DatasetBuilder {
  private var theLables:Option[List[String]] = None
  private var theTargets:Option[Seq[Int]] = None
  private var theInstances: List[Instance] = List()

  def labeled(lables: List[String]) = {theLables = Some(lables); this} /* returning this to enable method chaining. */
  def whereTargetsAre(targets: Seq[Int]) = {theTargets = Some(targets); this}
  def addInstance(instance: Instance) = {theInstances = instance :: theInstances; this}
  def ::(instance: Instance) = {addInstance(instance)}

  def build() = Dataset(theLables.get, theTargets.get, theInstances);
}


