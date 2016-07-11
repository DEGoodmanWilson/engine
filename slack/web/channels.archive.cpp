//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/channels.archive.h"
#include "private.h"

namespace slack { namespace channels
{

const std::string archive::error::CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const std::string archive::error::ALREADY_ARCHIVED = std::string{"already_archived"};
const std::string archive::error::CANT_ARCHIVE_GENERAL = std::string{"cant_archive_general"};
const std::string archive::error::LAST_RA_CHANNEL = std::string{"last_ra_channel"};
const std::string archive::error::RESTRICTED_ACTION = std::string{"restricted_action"};
const std::string archive::error::NOT_AUTHED = std::string{"not_authed"};
const std::string archive::error::INVALID_AUTH = std::string{"invalid_auth"};
const std::string archive::error::ACCOUNT_INACTIVE = std::string{"account_inactive"};
const std::string archive::error::USER_IS_BOT = std::string{"user_is_bot"};
const std::string archive::error::USER_IS_RESTRICTED = std::string{"user_is_restricted"};


archive::archive(const channel_id &channel) : channel_{channel}
{ }


void archive::initialize_()
{
    auto params = default_params({{"channel", channel_}});

    slack_private::get(this, "channels.archive", params);
}

}} //namespace channels slack
