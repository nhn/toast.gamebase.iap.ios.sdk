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

@property (nonatomic, copy, readonly) NSString *appKey;
@property (nonatomic, readonly) ToastGamebaseServiceZone serviceZone;
@property (nonatomic, copy, readonly, nullable) NSDictionary<NSString *, NSDictionary *> *extras;

+ (instancetype)configurationWithAppKey:(NSString *)appKey
                            serviceZone:(ToastGamebaseServiceZone)serviceZone;

- (void)addExtraObject:(NSDictionary *)object forStore:(NSString *)store;

@end

NS_ASSUME_NONNULL_END
