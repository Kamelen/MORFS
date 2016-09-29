package morfsengine

object main extends App{
  val dataset = DataLoader.getDatasetFromCsvFile("test.csv")
  print(dataset.toString)
}

//TODO : Dataset(Set of Sample's) representation
//TODO : Sample(Set of features) Representation
//TODO : Feature(mapping some feature name to a value) Representation

//TODO : Targets(Designates what features in the sample are the "outputs", allow for multiple since its MORandomForests)
//TODO : Tree representation
//TODO : Implement Bagging for the dataset(could this be a trait that can be added on a dataset that allows you to fetch a bagged subset)
//TODO : Implement Cross validation
//TODO : Be able to parse a .csv into a dataset
//TODO : Implement a "splitter"