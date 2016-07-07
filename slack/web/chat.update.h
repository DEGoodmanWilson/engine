//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <slack/types.h>
#include <slack/attachment.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace chat
{

class update :
        public slack::base::response
{
public:
    //public interface
    template<typename ...Os>
    update(const std::string& token, const ts &ts, const channel_id &channel, const std::string &text)
            : response{token}, ts_{ts}, channel_{channel}, text_{text}
    {
        initialize_();
    }

    template<typename ...Os>
    update(const std::string& token, const ts &ts, const channel_id &channel, const std::string &text, Os &&...os)
            : response{token}, ts_{ts}, channel_{channel}, text_{text}
    {
        slack::set_option<update>(*this, std::forward<Os>(os)...);
        initialize_();
    }

    //parameters
    struct parameter
    {
        using attachments = std::vector<slack::attachment>;
        enum class parse
        {
            none = 0,
            full,
        };

        MAKE_BOOL_LIKE(link_names);
    };

    //errors
    struct error :
            public slack::base::error
    {
        static const std::string MESSAGE_NOT_FOUND;
        static const std::string CHANNEL_NOT_FOUND;
        static const std::string CANT_DELETE_MESSAGE;
        static const std::string COMPLIANCE_EXPORTS_PREVENT_DELETION;
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
    };

    //response
    std::experimental::optional<slack::channel_id> channel;
    std::experimental::optional<slack::ts> ts;
    std::experimental::optional<std::string> text;

    //parameter setters
    void set_option(const parameter::parse &parse)
    { parse_ = parse; }

    void set_option(parameter::parse &&parse)
    { parse_ = std::move(parse); }

    void set_option(const parameter::link_names &link_names)
    { link_names_ = link_names; }

    void set_option(parameter::link_names &&link_names)
    { link_names_ = std::move(link_names); }

    void set_option(const parameter::attachments &attachments)
    { attachments_ = attachments; }

    void set_option(parameter::attachments &&attachments)
    { attachments_ = std::move(attachments); }

private:
    void initialize_();

    slack::ts ts_;

    channel_id channel_;
    std::string text_;
    std::experimental::optional<parameter::attachments> attachments_;
    std::experimental::optional<parameter::parse> parse_;
    std::experimental::optional<parameter::link_names> link_names_;
};

}} //namespace chat slack