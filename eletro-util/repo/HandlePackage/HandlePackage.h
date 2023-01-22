#ifndef MEDICALHORSE_HANDLEPACKAGE_H_
#define MEDICALHORSE_HANDLEPACKAGE_H_

#include <memory>
#include <algorithm>
#include "Package.h"

namespace medicalhorse::util::handlepackage
{
    class HandlePackage
    {
    public:
        /**
         * @brief Constructor
         */
        HandlePackage() = default;

        /**
         * @brief Destructor
         */
        virtual ~HandlePackage() = default;

        /**
         * @brief Insert element into data package
         * @param Content to insert
         * @result True when successful operation or False otherwise
         */
        static bool Validate(pdu_t pdu, bool isVerbose);

        /**
         * @brief Build
         * @param
         * @param
         * @param
         * @return
         */
        static std::shared_ptr<Package> Build(pdu_t pdu);

        /**
         * @brief Get the payload content from the package data
         *
         */
        static bool GetPayload(const std::shared_ptr<Package> &pPackage, pdu_t* pdu);


    private:
        static int8_t mFixedElementLen;
    };

} // namespace medicalhorse::util::handlepackage

#endif // MEDICALHORSE_HANDLEPACKAGE_H_