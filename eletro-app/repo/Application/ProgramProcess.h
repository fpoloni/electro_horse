#ifndef MEDICALHORSE_CRYOTHERAPY_H_
#define MEDICALHORSE_CRYOTHERAPY_H_

#include <memory>
#include <thread>

#include "Board.h"
#include "Common.h"
#include "ICommand.h"
#include "Package.h"
#include "HandlePackage.h"
#include "CommandDefinition.h"

namespace medicalhorse::command
{
    class ProgramProcess : public ICommand
    {
    public:
        /**
         * @brief Constructor
         */
        ProgramProcess(const std::shared_ptr<hardware::Board> &pBoard,
                    const util::definition::program::name &ProgramType);

        /**
         * @brief Destructor
         */
        virtual ~ProgramProcess() = default;

        /**
         * @brief
         */
        void Init();

        /**
         * @brief Method execute the process
         */
        void Start() override;

        /**
         * @brief Method Stop the started process
         */
        void Stop() override;

        bool Status(int *parameter) override;

        bool State(int *parameter) override;

        /**
         * @brief Method to load the device parameter on the board
         * @param device to set parameter
         * @param paramter tp set on the device
         */
        void Set(const int8_t device, const int parameter) override;

        /**
         * @Method to PDU update during preparation and run mode
         * @param pdu content to preparation and run control
         */ 
        void Set(const medicalhorse::util::pdu_t &pdu);

        /**
         * @brief Method to load the device parameter on the board
         * @param device to set parameter
         * @param paramter tp set on the device
         */
        void Get(const int8_t device, int *parameter) override;

        int GetCurrentTimeMinute();

        int GetCurrentTimeSeconds();

        

    private:
        void PumpControl(const int time);

        void SetTemperatureCtrl(const util::program::state control);
        /**
         * @brief Method to execute by loop the program
         * flow to keep the temperature control as well
         */
        void Run();

        /**
         * @brief Process to get temperature tank as expected
         * @param data - to set the state of process 
         */
        void RunProcess(const int8_t data);

        /**
         * @brief Process to get temperature tank as expected
         * @param data - to set the state of process 
         */
        void PreparationProcess(const int8_t data);

        /**
         * @brief Temperature control for Cryo process
         * @param temperature value
         */ 
        void CrioProcess(const int &temperature);

        /**
         * @brief Temperature control for Therm process
         * @param temperature value
         */ 
        void TermoProcess(const int &temperature);

    private:
        bool mIsStarted;
        bool mSetPackage;
        bool mIsTemperatureOk;
        int mManagePumpTime;
        int mManagePumpTimeState;
        uint8_t mStatusProgram;
        uint8_t mStateProgram;
        util::definition::program::name mProgramType;
        std::shared_ptr<hardware::Board> mpBoard;
        std::shared_ptr<std::thread> mpThreadRun;
        util::handlepackage::HandlePackage mHandlePackage;
        util::pdu_t mpdu;
    };

} // namespace medicalhorse::command

#endif //  MEDICALHORSE_CRYOTHERAPY_H_