//
//  ToastOngateConfiguration.h
//  ToastOngate
//
//  Created by NHNEnt on 2019. 1. 18..
//  Copyright © 2019년 NHNEnt. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, ToastOngateServiceZone) {
    ToastOngateServiceZoneReal,
    ToastOngateServiceZoneAlpha,
    ToastOngateServiceZoneBeta,
};

/**
 # ToastOngateConfiguration
 
 Configuration for ToastOngate SDK initialization.
 
 */
@interface ToastOngateConfiguration : NSObject

/** The app identifiers on the IAP console. */
@property (nonatomic, copy, readonly) NSString *appID;

/** The service zone(Real or Alpha or Beta). */
@property (nonatomic) ToastOngateServiceZone serviceZone;

/** The user ID for ToastOngate SDK. */
@property (nonatomic, strong) NSString *userID;

/**
 Initialize ToastOngateConfiguration with a given app key and userID.
 
 @param appID The app identifiers on the IAP console.
 @param userID The user ID for ToastOngate SDK.
 @return The instance of ToastOngateConfiguration.
 */
+ (ToastOngateConfiguration *)configurationWithAppID:(NSString *)appID
                                               userID:(NSString *)userID;

/**
 Initialize ToastOngateConfiguration with a given app key, userID and serviceZone.

 @param appID The app identifiers on the IAP console.
 @param userID The user ID for ToastOngate SDK.
 @param serviceZone The service zone(Real or Alpha or Beta).
 @return The instance of ToastOngateConfiguration.
 */
+ (ToastOngateConfiguration *)configurationWithAppID:(NSString *)appID
                                               userID:(NSString *)userID
                                          serviceZone:(ToastOngateServiceZone)serviceZone;

@end

NS_ASSUME_NONNULL_END
