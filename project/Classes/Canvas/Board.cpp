#include "Board.hpp"

BeaconApp::Board::Board() : m_graph(), m_connectivityRadius(Common::CommonDefs::DEFAULT_CONNECTIVITY_RADIUS)
{
    m_beacons.clear();

}

bool
BeaconApp::Board::addBeaconToBoard(cv::Point2d& point)
{
   BeaconApp::Beacon beacon(std::move(point), m_connectivityRadius);

   m_beacons.push_back(std::move(beacon));
   m_graph.addVertex();
   return createGraphEdges();
}

const std::vector<BeaconApp::Beacon>&
BeaconApp::Board::getBeaconsVec() const
{
    return m_beacons;
}

int
BeaconApp::Board::getStartBeaconIndex() const
{
    return 0;
}

int
BeaconApp::Board::getEndBeaconIndex() const
{
    int result = static_cast<int>(m_beacons.size());
    return (result > 0) ? result -1 :0;
}

std::vector<int>
BeaconApp::Board::getShortesPath()
{
    return m_graph.getShortestPath(getStartBeaconIndex(), getEndBeaconIndex());
}

bool
BeaconApp::Board::createGraphEdges()
{
    size_t circlesVecSize = m_beacons.size();

    for (int i = 0; i < circlesVecSize; ++i)
    {
        for (int j = i + 1; j < circlesVecSize; ++j)
        {
            double distance = m_beacons[i].calculateDistanceToCenter(m_beacons[j]);

            // Check if the center of circle i is inside the radius of circle j or vice versa
            if (distance <= m_beacons[j].getRadius())
            {
                try
                {
                    m_graph.addEdge(i, j, distance);
                }
                catch (...)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

