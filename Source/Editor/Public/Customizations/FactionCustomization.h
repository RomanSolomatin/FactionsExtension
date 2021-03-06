// Copyright 2015-2018 Piperift. All Rights Reserved.
#pragma once

#include "PropertyHandle.h"
#include "Customizations/StringEnumCustomization.h"


class FFactionCustomization : public FStringEnumCustomization
{
public:
    /**
    * Creates a new instance.
    *
    * @return A new struct customization for Factions.
    */
    static TSharedRef<IPropertyTypeCustomization> MakeInstance() 
    {
        return MakeShareable(new FFactionCustomization);
    }

protected:
    /** Handle to the struct properties being customized */
    TSharedPtr<IPropertyHandle> StructHandle;
    TSharedPtr<IPropertyHandle> IdHandle;
    
    virtual bool CanCustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

    /** Returns all the enum items.
    * This is for override purposes.
    */
    virtual void GetEnumItems(TArray<FString>& Values) const override;

    /** Returns all the enum items.
    * This is for override purposes.
    */
    virtual void OnItemSelected(FString Value) override;

    virtual FText GetSelectedItem() const override;
};

