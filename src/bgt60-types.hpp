/**
 * @file        bgt60-types.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Types
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_TYPES_HPP_
#define BGT60_TYPES_HPP_

namespace bgt60
{
    /**
    * \addtogroup bgt60api
    * @{
    */

    /**
    * @name   Error codes
    * @{
    */

    enum Error_t
    {
        OK          =  0,    /**< No error */
        INTF_ERROR  = -1,    /**< Interface error */
        CONF_ERROR  = -2,    /**< Configuration error */
        READ_ERROR  = -3,    /**< Read error */
        WRITE_ERROR = -4,    /**< Write error */
    };

    /** @} */

    /** @} */
}

#endif /** BGT60_TYPES_HPP_ **/