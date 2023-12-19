message Contract {
    double resource; // Required Computation Resource (delta)
    double reward; // Corresponding Reward (pi)
}

message ContractList {
    Contract contracts[];
}

message ContractChoice {
    int type;
}

message TaskMetadata {
    double taskResource;
    double taskDataSize;
    double delayConstraint;
}

message TaskAssignment {
    int fogNodeId;
    double price;
}
