

#include "linker.hpp"
#include <optional>
#include <iostream>
#include "Common/CommonDefs.hpp"
#include "Classes/Beacon/Beacon.hpp"
#include "Classes/Canvas/Board.hpp"

void Run()
{ 
    Common::CommonDefs::UserInput lastUserInput{};
    BeaconApp::Board board;
    bool updateCanvas = false;
    std::vector<int> indexesToDraw;
    indexesToDraw.clear();
    
    const auto GREEN = cv::Scalar(0, 255, 0);
    const auto RED = cv::Scalar(0, 0, 255);
    const auto BLUE = cv::Scalar(255, 0, 0);
    const auto CANVAS_WIDTH = 1920;
    const auto CANVAS_HEIGHT = 1024;

    cv::namedWindow("canvas", 1);
    cv::setMouseCallback("canvas", [](int event, int x, int y, int flags, void* userdata)
    {     
        if (event == cv::EVENT_LBUTTONDOWN)
        {
            auto userData = static_cast<Common::CommonDefs::UserInput*>(userdata);
            userData->mouse_press_pos = cv::Point2d{ static_cast<double>(x), static_cast<double>(y) };
        }
        //std::cout << "event" << event << std::endl;
        if (event == cv::EVENT_MOUSEWHEEL)
        {
            auto userData = static_cast<Common::CommonDefs::UserInput*>(userdata);

            userData->mouse_wheel_delta = cv::getMouseWheelDelta(flags);
        }
    }, &lastUserInput);



    cv::Mat canvas = cv::Mat::zeros(CANVAS_HEIGHT, CANVAS_WIDTH, CV_8UC3);

    std::optional<cv::Point2d> lastPoint{};

    while (true)
    {
        // clear canvas
        canvas.setTo(0);

        // TODO: handle user input
        if (lastUserInput.mouse_press_pos.has_value())
        {
            if (board.addBeaconToBoard(lastUserInput.mouse_press_pos.value()) == true)
                indexesToDraw = board.getShortesPath();

            lastUserInput.mouse_press_pos.reset();
            updateCanvas = true;
        }
        if (lastUserInput.mouse_wheel_delta.has_value())
        {          
            board.UpdateConectivityRadiusByDelta(lastUserInput.mouse_wheel_delta.value());
            lastUserInput.mouse_wheel_delta.reset();
        }

        cv::putText(canvas, "press 'c' to clear, 't' to toggle connectivity radius, escape to exit", cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1.3, GREEN, 2);
        cv::putText(canvas, cv::format("current connectivity radius = %d", board.GetConnectivityRadius()), cv::Point(20, 100), cv::FONT_HERSHEY_SIMPLEX, 1.3, GREEN, 2);

        // TODO draw shortest path


        if (updateCanvas)
        {
            auto beaconsToDraw = board.getBeaconsVec();

            for (size_t i = 0; i < beaconsToDraw.size(); ++i) 
            {

                cv::ellipse(canvas,
                    cv::Point((int)beaconsToDraw[i].getCenter().x, (int)beaconsToDraw[i].getCenter().y),
                    cv::Size((int)5, (int)5), 0.0,
                    0, 360,
                    GREEN, -1
                );

                cv::ellipse(canvas,
                    cv::Point((int)beaconsToDraw[i].getCenter().x, (int)beaconsToDraw[i].getCenter().y),
                    cv::Size((int)beaconsToDraw[i].getRadius(), (int)beaconsToDraw[i].getRadius()), 0.0,
                    0, 360,
                    BLUE, 3
                );
            }

            for (size_t i = 0; i < indexesToDraw.size() - 1; ++i) {
                int startIdx = indexesToDraw[i];
                int endIdx = indexesToDraw[i + 1];
                QPoint lineStart(circles[startIdx].getCenter().getX(), circles[startIdx].getCenter().getY());
                QPoint lineEnd(circles[endIdx].getCenter().getX(), circles[endIdx].getCenter().getY());

                shortestPathLines.push_back({ lineStart, lineEnd });
            }
        }

        cv::imshow("canvas", canvas);
        auto keyVal = cv::waitKey(1);

        if (keyVal != -1)
        {
            if (keyVal == 'c')
            {
                lastPoint.reset();
                // TODO: clear canvas
            }
            else if (keyVal == 't')
            {
                // TODO: toggle show / hide connectivity radius
            }
            else if (keyVal == 27) // escape
            {
                break; // exit program
            }
        }

    }

}


int main()
{
    Run();
    return 0;
}
