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
 * Contains a class that holds a plugin's instance config
 */

// Own header
#include <CppPluginFramework/PluginInstanceConfig.hpp>

// C++ Plugin Framework includes
#include <CppPluginFramework/Validation.hpp>

// Qt includes
#include <QtCore/QFileInfo>

// System includes

// Forward declarations

// Macros

namespace CppPluginFramework
{

PluginInstanceConfig::PluginInstanceConfig(const QString &name,
                                           const QJsonObject &config,
                                           const QSet<QString> &dependencies)
    : m_name(name),
      m_config(config),
      m_dependencies(dependencies)
{
}

// -------------------------------------------------------------------------------------------------

bool PluginInstanceConfig::isValid() const
{
    // Check name
    if (!Validation::validatePluginInstanceName(m_name))
    {
        return false;
    }

    // Config is optional

    // Check (optional) dependencies
    if (!m_dependencies.isEmpty())
    {
        // Check individual dependency if it is referencing a valid name
        for (const QString &dependency : m_dependencies)
        {
            if ((dependency == m_name) ||
                (!Validation::validatePluginInstanceName(dependency)))
            {
                return false;
            }
        }
    }

    return true;
}

// -------------------------------------------------------------------------------------------------

QString PluginInstanceConfig::name() const
{
    return m_name;
}

// -------------------------------------------------------------------------------------------------

void PluginInstanceConfig::setName(const QString &name)
{
    m_name = name;
}

// -------------------------------------------------------------------------------------------------

QJsonObject PluginInstanceConfig::config() const
{
    return m_config;
}

// -------------------------------------------------------------------------------------------------

void PluginInstanceConfig::setConfig(const QJsonObject &config)
{
    m_config = config;
}

// -------------------------------------------------------------------------------------------------

QSet<QString> PluginInstanceConfig::dependencies() const
{
    return m_dependencies;
}

// -------------------------------------------------------------------------------------------------

void PluginInstanceConfig::setDependencies(const QSet<QString> &dependencies)
{
    m_dependencies = dependencies;
}

// -------------------------------------------------------------------------------------------------

bool operator==(const PluginInstanceConfig &left, const PluginInstanceConfig &right)
{
    return ((left.name() == right.name()) &&
            (left.config() == right.config()) &&
            (left.dependencies() == right.dependencies()));
}

}
