//
//  ToastGamebaseIAPConfiguration.h
//  ToastGamebaseIAP
//
//  Created by Hyup on 17/04/2019.
//  Copyright © 2019 NHN. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ToastGamebaseConstant.h"

NS_ASSUME_NONNULL_BEGIN

@interface ToastGamebaseIAPConfiguration : NSObject <NSCoding, NSCopying>

//ToastOngate
@property (nonatomic, copy) NSString *ongateAppID;
@property (nonatomic, copy) NSString *ongateUserID;
@property (nonatomic) NSInteger ongateServiceZone;

//ToastIAP
@property (nonatomic, copy) NSString *userID;
@property (nonatomic, copy) NSString *appKey;
@property (nonatomic) NSInteger serviceZone;

+ (instancetype)configurationWithAppKey:(NSString *)appKey
                                 userID:(NSString *)userID
                            serviceZone:(ToastGamebaseServiceZone)serviceZone
                            ongateAppID:(NSString *)ongateAppID
                           ongateUserID:(NSString *)ongateUserID
                      ongateServiceZone:(ToastGamebaseServiceZone)ongateServiceZone;

+ (instancetype)configurationWithAppKey:(NSString *)appKey
                                 userID:(NSString *)userID
                            serviceZone:(ToastGamebaseServiceZone)serviceZone;

@end

NS_ASSUME_NONNULL_END
