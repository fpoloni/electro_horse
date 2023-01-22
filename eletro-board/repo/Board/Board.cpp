
#include "Board.h"
#include <algorithm>

namespace medicalhorse::hardware {
bool Board::mIsStarted = false;
bool Board::mIsInitialized = false;

std::shared_ptr<Board> Board::mpBoardInstance = nullptr;

std::shared_ptr<Board> Board::GetInstance() {
  if (nullptr == mpBoardInstance) {
    mpBoardInstance = std::shared_ptr<Board>(new Board);
  }
  return mpBoardInstance;
}

void Board::Init() {
  if (!mIsInitialized) {
    Add(BoardElement::first_type::Rele);
    Add(BoardElement::first_type::Motor);
    Add(BoardElement::first_type::Sensor);
    Add(BoardElement::first_type::Timer);
    Add(BoardElement::first_type::HBridge);

    printf("The board elements initialized.\n");

    mIsInitialized = true;
  }
}

void Board::Stop() {
  if (mIsStarted && mIsInitialized) {
    for (auto element : mListOfDevices) {
      element.second->Stop();
    }

    mIsStarted = false;
    mIsInitialized = false;
  }
}

bool Board::Start() {
  bool retVal = true;
  std::vector<device::definition::DeviceType>::iterator it;

  if (!mIsInitialized) {
    printf("Error to try the board component.\n");
    return false;
  }

  if (!mIsStarted) {
    printf("Starting board...\n");
    for (auto element : mListOfDevices) {
      it = find(mNoStartList.begin(), mNoStartList.end(), element.first);
      if (it == mNoStartList.end()) {
        bool temp = element.second->Start();
        printf("Device init: %d, %s\n", temp,
               element.second->GetName().c_str());
        retVal &= temp;
      }
    }

    mIsStarted = retVal;
  }

  return retVal;
}

bool Board::GetStructureDataBoardDevice(ElementBoard_t *element) {
  bool retVal = false;
  if (nullptr != element) {
    GetParameterToDevice(BoardElement::first_type::Sensor)
        ->GetParameter(&element->temperature);
    GetParameterToDevice(BoardElement::first_type::Motor)
        ->GetParameter(&element->pwmlevel);
    GetParameterToDevice(BoardElement::first_type::Timer)
        ->GetParameter(&element->time);

    retVal = true;
  }
  return retVal;
}

bool Board::SetParameterToDevice(const BoardElement::first_type deviceType,
                                 const int parameter) {
  return mListOfDevices[deviceType]->SetParameter(parameter);
}

std::shared_ptr<device::IDevices>
Board::GetParameterToDevice(const BoardElement::first_type deviceType) {
  return mListOfDevices[deviceType];
}

void Board::AddNotStartDevice(const device::definition::DeviceType element) {
  std::vector<device::definition::DeviceType>::iterator it;
  it = find(mNoStartList.begin(), mNoStartList.end(), element);
  if (it != mNoStartList.end())
    mNoStartList.push_back(element);
}

void Board::Add(const int device) {
  device::DeviceControl deviceControl;

  mListOfDevices.insert(
      std::make_pair<BoardElement::first_type, BoardElement::second_type>(
          static_cast<device::definition::DeviceType>(device),
          deviceControl.Create(
              static_cast<device::definition::DeviceType>(device))));
}

} // namespace medicalhorse::hardware
