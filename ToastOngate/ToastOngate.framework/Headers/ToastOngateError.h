//
//  ToastOngateError.h
//  ToastOngate
//
//  Created by NHNEnt on 2019. 1. 18..
//  Copyright © 2019년 NHNEnt. All rights reserved.
//

#ifndef ToastOngateError_h
#define ToastOngateError_h

static NSString *const ToastOngateErrorDomain       = @"com.toast.ongate";
static NSString *const ToastOngateMobillErrorDomain = @"com.toast.ongate.mobill";

typedef NS_ENUM(NSUInteger, ToastOngateErrorCode) {
    // Client Error (4xxxx)
    /** Initialization error. */
    ToastOngateErrorInitializationFailed    = 40001,
    
    /** User request failed. */
    ToastOngateErrorRequestFailed           = 40002,
    
    /** The identifier used by purchaseWithProductIdentifier is invalid. */
    ToastOngateErrorProductIdentifierInvalid= 40003,

    // Server Error (5xxxx)
    /** HTTP response code is not 20x. */
    ToastOngateErrorStatusInvalid           = 50001,
    
    /** Response is failed. */
    ToastOngateErrorResponseFailed          = 50002,
    
    /** API response is invalid. */
    ToastOngateErrorApiResponseInvalid      = 50003,
    
    // Ongate Error (6xxxx)
    /** Cash was insufficient for ONGATE. */
    ToastOngateErrorOngateCashInsufficient  = 60001,
};

typedef NS_ENUM(NSUInteger, ToastOngateHttpErrorCode) {
    
    /** No internet connection. */
    ToastOngateHttpErrorNotConnectedToInternet = 101,
    
    /** Request timeout. */
    ToastOngateHttpErrorTimeout = 102,
    
    /** Invalid URL. */
    ToastOngateHttpErrorURLInvalid = 103,
    
    /** Server response error. */
    ToastOngateHttpErrorResponseInvalid = 104,
    
    /** Allow Arbitrary Loads not set. */
    ToastOngateHttpErrorRequiresSecureConnection = 105,
    
    /** Network is failed. */
    ToastOngateHttpErrorNetworkFailed = 106,
};

#endif /* ToastOngateError_h */
