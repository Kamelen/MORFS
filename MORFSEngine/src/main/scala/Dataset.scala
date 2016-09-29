package morfsengine

/**
 * Created by epenerk on 8/21/16.
 */

object Dataset {
  type Dataset = List[Sample]
}

class Sample(inputFeatures : Vector[Feature], targetFeatures: Vector[Feature]){
  val features : Vector[Feature] = inputFeatures
  val targets : Vector[Feature] = targetFeatures

  override def toString: String = s"Instance { Input{${features.mkString}} Targets{${targets.mkString}}}${System.lineSeparator()}"
}

class Feature(name : String, value : Any) {
  val mapping = (name,value)

  override def toString: String = s"$name : $value"
}
