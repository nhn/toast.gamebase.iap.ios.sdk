//
//  ToastGamebasePurchaseResult.h
//  ToastGamebaseIAP
//
//  Created by Hyup on 17/04/2019.
//  Copyright © 2019 NHN. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ToastGamebaseConstant.h"

NS_ASSUME_NONNULL_BEGIN

@interface ToastGamebasePurchaseResult : NSObject <NSCoding, NSCopying>
{
    NSString *_store;
    NSString *_productIdentifier;
    ToastGamebaseProductType _productType;
    NSDecimalNumber *_price;
    NSString *_currency;
    NSString *_paymentSeq;
    NSString *_accessToken;
    NSString *_userID;
    BOOL _storePayment;    
    NSTimeInterval _purchaseTime;
    NSTimeInterval _expiryTime;
    NSString *_transactionIdentifier;
    NSString *_originalTransactionIdentifier;
}


@property (nonatomic, readonly, copy) NSString *store;
@property (nonatomic, readonly, copy) NSString *productIdentifier;
@property (nonatomic, readonly) ToastGamebaseProductType productType;
@property (nonatomic, readonly, copy) NSDecimalNumber *price;
@property (nonatomic, readonly, copy) NSString *currency;
@property (nonatomic, readonly, copy) NSString *paymentSeq;
@property (nonatomic, readonly, copy) NSString *accessToken;
@property (nonatomic, readonly, copy) NSString *userID;
@property (nonatomic, readonly, getter=isStorePayment) BOOL storePayment;
@property (nonatomic, readonly) NSTimeInterval purchaseTime;
@property (nonatomic, readonly) NSTimeInterval expiryTime;
@property (nonatomic, readonly, copy, nullable) NSString *transactionIdentifier;
@property (nonatomic, readonly, copy, nullable) NSString *originalTransactionIdentifier;

@end

NS_ASSUME_NONNULL_END
