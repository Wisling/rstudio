/*
 * RSessionContext.hpp
 *
 * Copyright (C) 2009-12 by RStudio, Inc.
 *
 * Unless you have received this program directly from RStudio pursuant
 * to the terms of a commercial license agreement with RStudio, then
 * this program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */

#ifndef CORE_R_UTIL_R_SESSION_CONTEXT_HPP
#define CORE_R_UTIL_R_SESSION_CONTEXT_HPP

#include <string>
#include <vector>

#include <boost/function.hpp>

#define kProjectNoneId "cfc78a31"
#define kWorkspacesId  "3c286bd3"

namespace rstudio {
namespace core {

class FilePath;

namespace r_util {

typedef boost::function<std::string(const std::string&)> ProjectIdToFilePath;
typedef boost::function<std::string(const std::string&)> FilePathToProjectId;

class SessionScope
{
private:
   SessionScope(const std::string& project, const std::string& id)
      : project_(project), id_(id)
   {
   }

public:

   static SessionScope fromProject(
                           std::string project,
                           const std::string& id,
                           const FilePathToProjectId& filePathToProjectId);

   static std::string projectPathForScope(
                           const SessionScope& scope,
                           const ProjectIdToFilePath& projectIdToFilePath);

   static SessionScope fromProjectId(const std::string& project,
                                     const std::string& id);

   static SessionScope projectNone(const std::string& id);

   SessionScope()
   {
   }

   bool isProjectNone() const;

   const std::string& project() const { return project_; }

   const std::string& id() const { return id_; }

   bool empty() const { return project_.empty(); }

   bool operator==(const SessionScope &other) const {
      return project_ == other.project_ && id_ == other.id_;
   }

   bool operator!=(const SessionScope &other) const {
      return !(*this == other);
   }

   bool operator<(const SessionScope &other) const {
       return project_ < other.project_ ||
              (project_ == other.project_ && id_ < other.id_);
   }

private:
   std::string project_;
   std::string id_;
};


bool validateSessionScopeId(const FilePath& userScratchPath,
                            const std::string& id);

bool validateProjectSessionScope(
           const SessionScope& scope,
           const core::FilePath& userHomePath,
           const core::FilePath& userScratchPath,
           core::r_util::ProjectIdToFilePath projectIdToFilePath,
           std::string* pProjectFilePath);

std::string urlPathForSessionScope(const SessionScope& scope);

std::string createSessionUrl(const std::string& hostPageUrl,
                             const SessionScope& scope);

void parseSessionUrl(const std::string& url,
                     SessionScope* pScope,
                     std::string* pUrlPrefix,
                     std::string* pUrlWithoutPrefix);


struct SessionContext
{
   SessionContext()
   {
   }

   explicit SessionContext(const std::string& username,
                           const SessionScope& scope = SessionScope())
      : username(username), scope(scope)
   {
   }
   std::string username;
   SessionScope scope;

   bool empty() const { return username.empty(); }

   bool operator==(const SessionContext &other) const {
      return username == other.username && scope == other.scope;
   }

   bool operator<(const SessionContext &other) const {
       return username < other.username ||
              (username == other.username && scope < other.scope);
   }
};


std::ostream& operator<< (std::ostream& os, const SessionContext& context);

std::string sessionScopeFile(std::string prefix,
                             const SessionScope& scope);

std::string sessionScopePrefix(const std::string& username);

std::string sessionScopesPrefix(const std::string& username);

std::string sessionContextFile(const SessionContext& context);

std::string generateScopeId();
std::string generateScopeId(const std::vector<std::string>& reserved);


} // namespace r_util
} // namespace core 
} // namespace rstudio


#endif // CORE_R_UTIL_R_SESSION_CONTEXT_HPP

