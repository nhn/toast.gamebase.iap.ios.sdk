//
//  ToastGamebaseConstant.h
//  ToastGamebaseIAP
//
//  Created by Hyup on 18/04/2019.
//  Copyright © 2019 NHN. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, ToastGamebaseServiceZone) {
    ToastGamebaseServiceZoneReal    = 0,
    ToastGamebaseServiceZoneAlpha   = 1,
    ToastGamebaseServiceZoneBeta    = 2,
};

typedef NS_ENUM(NSInteger, ToastGamebaseProductType) {
    ToastGamebaseProductTypeUnknown                     = 0,
    ToastGamebaseProductTypeConsumable                  = 1,
    ToastGamebaseProductTypeAutoRenewableSubscription   = 2,
};

typedef NS_ENUM(NSInteger, ToastGamebaseIAPErrorCode) {
    
    //ToastGamebase Error Code
    ToastGamebaseIAPErrorCodeStoreNotMatched         = 10001,
    
    ToastGamebaseIAPErrorCodeNotSupportedMethod      = 10008,
    ToastGamebaseIAPErrorCodeNotImportedFramework    = 10009,
    
    //ToastGamebase Ongate Only Code
    ToastGamebaseIAPErrorOngateCashInsufficient      = 60001,
};

//StoreCode
extern NSString *const ToastGamebaseStoreAppStore;
extern NSString *const ToastGamebaseStoreOngate;

//Error
extern NSString *const ToastGamebaseIAPErrorDomain;

//Error Key
extern NSString *const kToastGamebaseIsStorePayment;
extern NSString *const kToastGamebaseCauseError;

//Configuration Key
extern NSString *const kToastProviderAppID;
extern NSString *const kToastProviderUserID;


