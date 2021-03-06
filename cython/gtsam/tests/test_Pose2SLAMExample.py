import unittest
import gtsam
from math import pi
import numpy as np

class TestPose2SLAMExample(unittest.TestCase):

    def test_Pose2SLAMExample(self):
        # Assumptions
        #  - All values are axis aligned
        #  - Robot poses are facing along the X axis (horizontal, to the right in images)
        #  - We have full odometry for measurements
        #  - The robot is on a grid, moving 2 meters each step

        # Create graph container and add factors to it
        graph = gtsam.NonlinearFactorGraph()

        # Add prior
        # gaussian for prior
        priorMean = gtsam.Pose2(0.0, 0.0, 0.0)  # prior at origin
        priorNoise = gtsam.noiseModel_Diagonal.Sigmas(np.array([0.3, 0.3, 0.1]))
        # add directly to graph
        graph.add(gtsam.PriorFactorPose2(1, priorMean, priorNoise))

        # Add odometry
        # general noisemodel for odometry
        odometryNoise = gtsam.noiseModel_Diagonal.Sigmas(np.array([0.2, 0.2, 0.1]))
        graph.add(gtsam.BetweenFactorPose2(
            1, 2, gtsam.Pose2(2.0, 0.0, 0.0), odometryNoise))
        graph.add(gtsam.BetweenFactorPose2(
            2, 3, gtsam.Pose2(2.0, 0.0, pi / 2), odometryNoise))
        graph.add(gtsam.BetweenFactorPose2(
            3, 4, gtsam.Pose2(2.0, 0.0, pi / 2), odometryNoise))
        graph.add(gtsam.BetweenFactorPose2(
            4, 5, gtsam.Pose2(2.0, 0.0, pi / 2), odometryNoise))

        # Add pose constraint
        model = gtsam.noiseModel_Diagonal.Sigmas(np.array([0.2, 0.2, 0.1]))
        graph.add(gtsam.BetweenFactorPose2(5, 2, gtsam.Pose2(2.0, 0.0, pi / 2), model))

        # Initialize to noisy points
        initialEstimate = gtsam.Values()
        initialEstimate.insert(1, gtsam.Pose2(0.5, 0.0, 0.2))
        initialEstimate.insert(2, gtsam.Pose2(2.3, 0.1, -0.2))
        initialEstimate.insert(3, gtsam.Pose2(4.1, 0.1, pi / 2))
        initialEstimate.insert(4, gtsam.Pose2(4.0, 2.0, pi))
        initialEstimate.insert(5, gtsam.Pose2(2.1, 2.1, -pi / 2))

        # Optimize using Levenberg-Marquardt optimization with an ordering from
        # colamd
        optimizer = gtsam.LevenbergMarquardtOptimizer(graph, initialEstimate)
        result = optimizer.optimizeSafely()

        # Plot Covariance Ellipses
        marginals = gtsam.Marginals(graph, result)
        P = marginals.marginalCovariance(1)

        pose_1 = result.atPose2(1)
        self.assertTrue(pose_1.equals(gtsam.Pose2(), 1e-4))

if __name__ == "__main__":
    unittest.main()
