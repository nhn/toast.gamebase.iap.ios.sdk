//
//  ToastOngatePurchaseResult.h
//  ToastOngate
//
//  Created by NHNEnt on 23/01/2019.
//  Copyright © 2019 NHNEnt. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 # ToastOngatePurchaseResult
 
 The result of purchase.
 
 It used in
 
 * [ToastOngate requestConsumablePurchasesWithCompletionHandler:]
 * [ToastOngate consumeWithPurchaseResult:completionHandler:]
 * [ToastOngatePurchaseDelegate didReceivePurchaseResult:]
 
 */
@interface ToastOngatePurchaseResult : NSObject

/** The payment sequence of purchase(Issued from the IAP server). */
@property (nonatomic, strong) NSString *paymentSeq;

/** The token issued after purchase. */
@property (nonatomic, strong) NSString *purchaseToken;

/** The sequence of product. */
@property (nonatomic, assign) long productSeq;

/** The identifier of product. */
@property (nonatomic, strong) NSString *productIdentifier;

/** The price of purchase. */
@property (nonatomic, strong, nullable) NSDecimalNumber *price;

/** The currency of purchse. */
@property (nonatomic, strong, nullable) NSString *currency;

- (instancetype)initWithPaymentSeq:(NSString *)paymentSeq
                     purchaseToken:(NSString *)purchaseToken
                 productIdentifier:(NSString *)productIdentifier
                        productSeq:(NSNumber *)productSeq
                             price:(NSDecimalNumber *)price
                          currency:(NSString *)currency;

+ (instancetype)paymentSeq:(NSString *)paymentSeq
             purchaseToken:(NSString *)purchaseToken
         productIdentifier:(NSString *)productIdentifier
                productSeq:(NSNumber *)productSeq
                     price:(NSDecimalNumber *)price
                  currency:(NSString *)currency;
@end

NS_ASSUME_NONNULL_END
