/**
 * Created by epenerk on 8/21/16.
 */
class Dataset(source: DataSource) {
  val samples : List[Sample] = source.getFeaturesFromSource
}

class Sample(inputFeatures : Vector[Feature], targetsIndexes: List[Int]){
  val features : Vector[Feature] = inputFeatures
  val targets : List[Int] = targetsIndexes

  override def toString: String = s"Sample { Features{$features} Targets{$targets} }"
}

class Feature(name : String, value : AnyVal) {
  val mapping = (name,value)

  override def toString: String = s"$name : $value"
}
