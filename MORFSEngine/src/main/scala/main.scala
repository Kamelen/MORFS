package morfsengine

object main extends App{
  val dataset = DataLoader.getDatasetFromCsvFile("test.csv")
  print(dataset.toString)
}
//TODO : Implement a nice DSL for constructing a dataset(Builder pattern?)
//TODO : Tree representation
//TODO : Implement Bagging for the dataset(could this be a trait that can be added on a dataset that allows you to fetch a bagged subset)
//TODO : Implement Cross validation
//TODO : Be able to parse a .csv into a dataset
//TODO : Implement a "splitter"