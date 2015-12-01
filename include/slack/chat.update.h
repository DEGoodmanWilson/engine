//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <slack/base/impl.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack
{
namespace chat
{

/*************************************************************/
// MARK: - Parameters

namespace parameter
{
namespace update
{

//This one needs to be better!!
MAKE_STRING_LIKE(attachments);
enum class parse
{
    none = 0,
    full,
};
MAKE_BOOL_LIKE(link_names);

} //namespace update
} //namespace parameter

/*************************************************************/
// MARK: - Response Errors

namespace response
{
namespace error
{
namespace update
{

const auto UNKNOWN = std::string{"unknown"};
const auto JSON_PARSE_FAILURE = std::string{"json_parse_failure"};
const auto INVALID_RESPONSE = std::string{"invalid_response"};
const auto MESSAGE_NOT_FOUND = std::string{"message_not_found"};
const auto CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
const auto CANT_DELETE_MESSAGE = std::string{"cant_delete_message"};
const auto COMPLIANCE_EXPORTS_PREVENT_DELETION = std::string{"compliance_exports_prevent_deletion"};
const auto NOT_AUTHED = std::string{"not_authed"};
const auto INVALID_AUTH = std::string{"invalid_auth"};
const auto ACCOUNT_INACTIVE = std::string{"account_inactive"};

} //namespace update
} //namespace error
} //namespace response


/*************************************************************/
// MARK: - Response

namespace response
{

struct update :
        public slack::base::response
{
    update(const std::string &raw_json);

    std::experimental::optional<channel_id> channel;
    std::experimental::optional<ts> ts;
    std::experimental::optional<std::string> text;
};

} //namespace response


/*************************************************************/
// MARK: - Impl

namespace impl
{

class update :
        public slack::base::impl<response::update>
{
public:
    update(const ts &ts, const channel_id &channel, const std::string &text);
    //TODO can these be moved into the base class?
    response::update get_response();

    void set_option(const parameter::update::parse &parse)
    { parse_ = parse; }

    void set_option(parameter::update::parse &&parse)
    { parse_ = std::move(parse); }

    void set_option(const parameter::update::link_names &link_names)
    { link_names_ = link_names; }

    void set_option(parameter::update::link_names &&link_names)
    { link_names_ = std::move(link_names); }

    void set_option(const parameter::update::attachments &attachments)
    { attachments_ = attachments; }

    void set_option(parameter::update::attachments &&attachments)
    { attachments_ = std::move(attachments); }

private:
    ts ts_;
    channel_id channel_;
    std::string text_;
    std::experimental::optional<parameter::update::attachments> attachments_;
    std::experimental::optional<parameter::update::parse> parse_;
    std::experimental::optional<parameter::update::link_names> link_names_;
};

} //namespace impl


/*************************************************************/
// MARK: - Public Interface


template<typename ...Os>
response::update update(const ts &ts, const channel_id &channel, const std::string &text)
{
    class impl::update impl{ts, channel, text};
    return impl.get_response();
}

template<typename ...Os>
response::update update(const ts &ts, const channel_id &channel, const std::string &text, Os &&...os)
{
    class impl::update impl{ts, channel, text};
    set_option<decltype(impl)>(impl, std::forward<Os>(os)...);
    return impl.get_response();
}

} //namespace chat
} //namespace slack