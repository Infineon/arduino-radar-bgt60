/**
 * @file        bgt60-conf.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Library Configuration
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_CONF_HPP_
#define BGT60_CONF_HPP_

#include "bgt60-conf-opts.hpp"

#ifndef BGT60_LOGGER_ENABLED
#define BGT60_LOGGER_ENABLED    0   /**< (1) Enabled, (0) Disabled */
#endif

/**
 * @brief Enable each logger module
 */
#if (BGT60_LOGGER_ENABLED == 1)

#define BGT60_CORE_LOGGER_ENABLED   1               /**< Core module */
#define BGT60_APP_LOGGER_ENABLED    1               /**< Application level module */

#endif

#include "bgt60-conf-dfl.hpp"

/** @} */

#endif /** BGT60_CONF_HPP_ **/