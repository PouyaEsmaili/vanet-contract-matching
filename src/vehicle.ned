package contractbased;

simple Vehicle {
    parameters:
        double totalResource; // Total Available Computation Resource (delta m,0)
        double taskDataSize; // (D)
        double taskResource; // (C)
        double delayConstraint; // (tao)
    gates:
        inout baseStation;
        inout vehicles[];
}