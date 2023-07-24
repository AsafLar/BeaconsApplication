#ifndef BOARD_HPP
#define BOARD_HPP

#include "../Beacon/Beacon.hpp"
#include "../Graph/Graph.hpp"
#include "../../Common/CommonDefs.hpp"
#include <vector>
#include <iostream>


namespace BeaconApp {

    /// @class   Board
    ///
    /// @brief   A representation of a board containing circles and their connections.
    ///          This class manages a collection of circles placed on the board and maintains a graph
    ///          to represent the connections between these circles. It provides methods to add circles,
    ///          find the shortest path between two circles, and manage the underlying graph.
    ///
    /// @date    24/07/2023
    class Board {
    private:
        std::vector<BeaconApp::Beacon> m_beacons;
        DijakstraAlgo::Graph m_graph;
        int m_connectivityRadius;

    public:
        /// @brief Default constructor for the Board class.
        ///
        /// Creates a Board object with an empty vector of circles and an initialized graph.
        Board();

        /// @brief Adds a circle with the specified point and radius to the board.
        ///
        /// @param point The center point of the new circle.
        /// @param radius The radius of the new circle.
        /// @return True if the circle was successfully added to the board, false otherwise.
        bool addBeaconToBoard(cv::Point2d& point);

        /// @brief Getter method to access the vector containing the circles on the board.
        ///
        /// @return A constant reference to the vector of circles on the board.
        const std::vector<BeaconApp::Beacon>& getBeaconsVec() const;

        /// @brief Get the index of the start circle on the board.
        ///
        /// The start circle is the one that will serve as the source vertex for shortest path calculations.
        /// @return The index of the start circle in the m_circles vector.
        int getStartBeaconIndex() const;

        /// @brief Get the index of the end circle on the board.
        ///
        /// The end circle is the one that will serve as the destination vertex for shortest path calculations.
        /// @return The index of the end circle in the m_circles vector.
        int getEndBeaconIndex() const;

        /// @brief Calculates the shortest path between the start circle and end circle on the board.
        ///
        /// The calculation is performed using Dijkstra's algorithm based on the underlying graph.
        /// @return A vector of integers representing the indices of the circles in the shortest path.
        std::vector<int> getShortesPath();

        /// @brief Creates the edges for the graph representing connections between circles on the board.
        ///
        /// The function establishes edges between circles based on their adjacency in the m_circles vector.
        /// @return True if the graph edges were successfully created, false otherwise.
        bool createGraphEdges();


        void UpdateConectivityRadiusByDelta(int delta)
        {
            static constexpr int MOUSE_WHEEL_DEFAULT_GRANULARITY = 120;
            auto radiusDelta = (delta / MOUSE_WHEEL_DEFAULT_GRANULARITY) * Common::CommonDefs::CONNECTIVITY_RADIUS_GRANULARITY;
            m_connectivityRadius = std::clamp(m_connectivityRadius + radiusDelta, Common::CommonDefs::MIN_CONNECTIVITY_RADIUS, Common::CommonDefs::MAX_CONNECTIVITY_RADIUS);
        }

        int GetConnectivityRadius()
        {
            return m_connectivityRadius;
        }
    };
}

#endif // BOARD_HPP
