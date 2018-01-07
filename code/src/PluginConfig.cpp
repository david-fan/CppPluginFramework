/* This file is part of C++ Plugin Framework.
 *
 * C++ Plugin Framework is free software: you can redistribute it and/or modify it under the terms
 * of the GNU Lesser General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * C++ Plugin Framework is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with C++ Plugin
 * Framework. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file
 *
 * Contains a class that holds a plugin's config
 */

// C++ Plugin Framework includes
#include <CppPluginFramework/PluginConfig.hpp>
#include <CppPluginFramework/Validation.hpp>

// Qt includes
#include <QtCore/QFileInfo>

// System includes

// Forward declarations

// Macros

namespace CppPluginFramework
{

PluginConfig::PluginConfig(const QString &filePath, const VersionInfo &version)
    : m_filePath(filePath),
      m_version(version),
      m_minVersion(),
      m_maxVersion(),
      m_instanceConfigs()
{
}

PluginConfig::PluginConfig(const QString &filePath,
                           const VersionInfo &minVersion,
                           const VersionInfo &maxVersion)
    : m_filePath(filePath),
      m_version(),
      m_minVersion(minVersion),
      m_maxVersion(maxVersion),
      m_instanceConfigs()
{
}

bool PluginConfig::isValid() const
{
    // Check file path
    bool valid = QFileInfo(m_filePath).isFile();

    // Check version info
    if (valid)
    {
        if (isExactVersion())
        {
            valid = m_version.isValid();
        }
        else
        {
            valid = VersionInfo::isRangeValid(m_minVersion, m_maxVersion);
        }
    }

    // Check instance configs
    if (valid)
    {
        // At least one plugin instance is required
        valid = !m_instanceConfigs.isEmpty();

        // Check individual dependency if it is referencing a valid name
        if (valid)
        {
            for (const PluginInstanceConfig &instanceConfig : m_instanceConfigs)
            {
                if (!instanceConfig.isValid())
                {
                    valid = false;
                    break;
                }
            }
        }
    }

    return valid;
}

bool PluginConfig::isExactVersion() const
{
    return ((!m_version.isNull()) && m_minVersion.isNull() && m_maxVersion.isNull());
}

bool PluginConfig::isVersionRange() const
{
    return (m_version.isNull() && (!m_minVersion.isNull()) && (!m_maxVersion.isNull()));
}

QString PluginConfig::filePath() const
{
    return m_filePath;
}

void PluginConfig::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

VersionInfo PluginConfig::version() const
{
    return m_version;
}

void PluginConfig::setVersion(const VersionInfo &version)
{
    m_version = version;
}

VersionInfo PluginConfig::minVersion() const
{
    return m_minVersion;
}

void PluginConfig::setMinVersion(const VersionInfo &minVersion)
{
    m_minVersion = minVersion;
}

VersionInfo PluginConfig::maxVersion() const
{
    return m_maxVersion;
}

void PluginConfig::setMaxVersion(const VersionInfo &maxVersion)
{
    m_maxVersion = maxVersion;
}

QList<PluginInstanceConfig> PluginConfig::instanceConfigs() const
{
    return m_instanceConfigs;
}

void PluginConfig::setInstanceConfigs(const QList<PluginInstanceConfig> &instanceConfigs)
{
    m_instanceConfigs = instanceConfigs;
}

}
