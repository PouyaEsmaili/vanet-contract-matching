package contractbased;

simple BaseStation {
    parameters:
        double unitBenefit;
        double computationCapability;
        int duration;
        string typeProbability[];
        int totalVehicles;
        double deltaMin;
        double deltaMax;

        int taskAssignmentThreshold;
    gates:
        inout vehicles[];
}