/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "Element.h"
#include "EngineDefinition.h"
#include <Volume.h>
#include <RoutingStrategy.h>
#include <map>

namespace android
{
namespace audio_policy
{
/**
 * @tparam routing_strategy: Applicable strategy for this stream.
 */
template <>
class Element<audio_stream_type_t>
{
private:
    typedef std::map<Volume::device_category, VolumeCurvePoints> VolumeProfiles;
    typedef VolumeProfiles::iterator VolumeProfileIterator;
    typedef VolumeProfiles::const_iterator VolumeProfileConstIterator;

public:
    Element(const std::string &name)
        : mName(name),
          mApplicableStrategy(STRATEGY_MEDIA),
          mIndexMin(0),
          mIndexMax(1)
    {}
    ~Element() {}

    /**
     * Returns identifier of this policy element
     *
     * @returns string representing the name of this policy element
     */
    const std::string &getName() const { return mName; }

    /**
    * Set the unique identifier for this policy element.
    *
    * @tparam Key type of the unique identifier.
    * @param[in] identifier to be set.
    *
    * @return NO_ERROR if the identifier is valid and set correctly, error code otherwise.
    */
    status_t setIdentifier(audio_stream_type_t identifier);

    /**
     * @return the unique identifier of this policy element.
     */
    audio_stream_type_t getIdentifier() const { return mIdentifier; }

    /**
     * A Policy element may implement getter/setter function for a given property.
     * Property may be routing_strategy, audio_stream_type_t, audio_usage_t, audio_source_t
     * or a string.
     */
    template <typename Property>
    Property get() const;

    template <typename Property>
    status_t set(Property property);

    status_t setVolumeProfile(Volume::device_category category, const VolumeCurvePoints &points);

    float volIndexToDb(Volume::device_category deviceCategory, int indexInUi);

    status_t initVolume(int indexMin, int indexMax);

private:
    /* Copy facilities are put private to disable copy. */
    Element(const Element &object);
    Element &operator=(const Element &object);

    std::string mName; /**< Unique literal Identifier of a policy base element*/
    audio_stream_type_t mIdentifier; /**< Unique numerical Identifier of a policy base element*/

    routing_strategy mApplicableStrategy; /**< Applicable strategy for this stream. */

    /**
     * Collection of volume profiles indexed by the stream type.
     * Volume is the only reason why the stream profile was not removed from policy when introducing
     * attributes.
     */
    VolumeProfiles mVolumeProfiles;

    int mIndexMin;

    int mIndexMax;
};

typedef Element<audio_stream_type_t> Stream;

} // namespace audio_policy
} // namespace android


