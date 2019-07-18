//
//  ToastGamebaseProduct.h
//  ToastGamebaseIAP
//
//  Created by Hyup on 17/04/2019.
//  Copyright © 2019 NHN. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ToastGamebaseConstant.h"

NS_ASSUME_NONNULL_BEGIN

@interface ToastGamebaseProduct : NSObject <NSCoding, NSCopying>
{
    NSString *_store;
    ToastGamebaseProductType _productType;
    NSString *_productID;
    NSInteger _productSeq;
    NSString *_productName;
    NSDecimalNumber *_price;
    NSString *_currency;
    NSString *_localizedPrice;
    BOOL _active;
}

@property (nonatomic, readonly, copy) NSString *store;
@property (nonatomic, readonly) ToastGamebaseProductType productType;
@property (nonatomic, readonly, copy) NSString *productID;
@property (nonatomic, readonly) NSInteger productSeq;
@property (nonatomic, readonly, copy, nullable) NSString *productName;
@property (nonatomic, readonly, copy, nullable) NSDecimalNumber *price;
@property (nonatomic, readonly, copy, nullable) NSString *currency;
@property (nonatomic, readonly, copy, nullable) NSString *localizedPrice;
@property (nonatomic, readonly, getter=isActive) BOOL active;

@end

NS_ASSUME_NONNULL_END
