
#ifndef MEDICALHORSE_BOARD_H_
#define MEDICALHORSE_BOARD_H_

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "Common.h"
#include "Device/IDevices.h"
#include "Device/DeviceDefinition.h"
#include "../DeviceControl/DeviceControl.h"

namespace medicalhorse {
namespace hardware {

typedef std::pair<device::definition::DeviceType, std::shared_ptr<device::IDevices>> BoardElement;

/**
 * @brief
 */
typedef struct {
    std::string name;
    int temperature;
    int pwmlevel;
    int time;

} ElementBoard_t;

class Board
{
     public:
        Board(Board &other) = delete;

        /**
         * @brief
         */
        static std::shared_ptr<Board> GetInstance();

        /**
         * @brief Init the component
         */
        void Init();

        void Stop();

        bool Start();


        /**
         * @brief Operator to avoid unexpected component instance
         * @param Class object
         */
        void operator=(const Board&) = delete;

        /**
         * @brief Get set paramenters from all elements added in the board
         * @param element - Group of elements available on the board
         * @return true for successfuly access or false otherwise
         */
        bool GetStructureDataBoardDevice(ElementBoard_t *element);

        /**
         * @brief
         * @param
         * @return
         */
        std::shared_ptr<device::IDevices> GetParameterToDevice(const BoardElement::first_type deviceType);

        /**
         * @brief Set the parameter to the specific element on the board
         * @param deviceType - Group of the devices available on the board
         * @param parameter - Parameter to set to device
         * @return true for successfuly access or false otherwise
         */
        bool SetParameterToDevice(const BoardElement::first_type deviceType, const int parameter);


        void AddNotStartDevice(const device::definition::DeviceType element);


    private:
        /**
         * @brief Methods
         */
        Board() = default;
        void Add(const int device);

    private:
        /**
         * @brief Attributes
         */
        static bool mIsStarted;
        static bool mIsInitialized;
        static std::shared_ptr<Board> mpBoardInstance;

        std::vector<device::definition::DeviceType> mNoStartList;
        std::unordered_map<device::definition::DeviceType, std::shared_ptr<device::IDevices>> mListOfDevices;
};

}  // namespace hardware
}  // namespace medicalhorse

#endif // MEDICALHORSE_BOARD_H_