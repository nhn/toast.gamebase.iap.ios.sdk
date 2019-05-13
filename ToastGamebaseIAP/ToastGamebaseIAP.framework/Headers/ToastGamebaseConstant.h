//
//  ToastGamebaseConstant.h
//  ToastGamebaseIAP
//
//  Created by Hyup on 18/04/2019.
//  Copyright © 2019 NHN. All rights reserved.
//

#ifndef ToastGamebaseConstant_h
#define ToastGamebaseConstant_h

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

static NSString *const ToastGamebaseStoreAppStore   = @"APPSTORE";
static NSString *const ToastGamebaseStoreOngate     = @"ONGATE";

static NSString *const ToastGamebaseIAPErrorDomain = @"com.toast.iap.gamebase";

static NSString *const kToastGamebaseIsStorePayment = @"isStorePayment";
static NSString *const kToastGamebaseOriginalError  = @"originalError";


static NSString *const ToastGamebaseDidReceivePurchaseResultNotification = @"ToastGamebaseDidReceivePurchaseResult";
static NSString *const ToastGamebaseDidFailPurchaseProductNotification = @"ToastGamebaseDidFailPurchaseProduct";

static NSString *const ToastGamebasePurchaseResultNotification = @"ToastGamebasePurchaseResultNotification";


#endif /* ToastGamebaseConstant_h */

