#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <opencv2/core.hpp>


/// @class   Beacon
///
/// @brief   A beacon class implementation representing a 2d point and radius.
///          This class provides methods to set and get the center point and radius, as well as to calculate
///          the distance between the centers of two beacons.
///
/// @date    24/07/2023
namespace BeaconApp {

    class Beacon {
    private:
        cv::Point2d m_centerPoint;
        double m_radius;

    public:

        /// @brief Constructor for the Circle class
        ///
        /// @param center The center point of the circle
        /// @param r The radius of the circle
        Beacon(const cv::Point2d& p, double r) : m_centerPoint(p), m_radius(r)
        {

        }

        /// @brief Getter function for the center point of the circle
        ///
        /// @return A constant reference to the center point of the circle
        const cv::Point2d& getCenter() const
        {
            return m_centerPoint;
        }

        /// @brief Setter function for the center point of the circle
        ///
        /// @param x The x-coordinate value of the new center point
        /// @param y The y-coordinate value of the new center point
        void setCenter(double x, double y)
        {
            m_centerPoint.x = x;
            m_centerPoint.y = y;
        }

        /// @brief Getter function for the radius of the circle
        ///
        /// @return The radius of the circle
        double getRadius() const
        {
            return m_radius;
        }

        /// @brief Setter function for the radius of the circle
        ///
        /// @param r The new radius value for the circle
        void setRadius(double r)
        {
            m_radius = r;
        }

        /// @brief Calculate the distance between the centers of this circle and another circle
        ///
        /// @param other The other circle to calculate the distance to its center
        /// @return The distance between the centers of the two circles
        double calculateDistanceToCenter(const Beacon& other) const
        {
            cv::Point2d diffPoint = m_centerPoint - other.m_centerPoint;
            return std::sqrt(diffPoint.x * diffPoint.x + diffPoint.y * diffPoint.y);
        }
    };
}



#endif // CIRCLE_HPP
