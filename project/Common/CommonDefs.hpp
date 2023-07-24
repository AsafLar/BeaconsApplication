#ifndef COMMONDEFS_H
#define COMMONDEFS_H

#pragma once
#include <optional>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace Common {

	class CommonDefs
	{
	public:
		static inline constexpr int CONNECTIVITY_RADIUS_GRANULARITY = 10;
		static inline constexpr int DEFAULT_CONNECTIVITY_RADIUS = 100;
		static inline constexpr int MIN_CONNECTIVITY_RADIUS = 10;
		static inline constexpr int MAX_CONNECTIVITY_RADIUS = 1000;

		// a struct for representing optional user input
		// for a certain frame
		struct UserInput
		{
			std::optional<cv::Point2d> mouse_press_pos;
			std::optional<int>         mouse_wheel_delta;
		};
	};
}


#endif // COMMONDEFS_H



