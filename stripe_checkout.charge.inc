<?php
/**
 * @file
 * Contains implementation of a page to charge the card for Stripe Checkout
 */

function stripe_checkout_charge() {
  if (isset($_POST['stripeToken'])) { $token = $_POST['stripeToken']; }
  
  if (!empty($token)) {
    $tokentype = $_POST['stripeTokenType'];
    $email = $_POST['stripeEmail'];
    $amount = check_plain(($_POST['data-amount'])*100);
    $_SESSION['stripe_checkout_amount_cents'] = $amount;
    
    $apiconfig = config('stripe_api.settings');
    $secretconfig = config('stripe_api_secret.settings');
    $checkoutconfig = config('stripe_checkout.settings');
    
    $mode = $apiconfig->get('stripe_api_mode');
    if ($mode === 'live') {
      $key = $secretconfig->get('stripe_api_live_secret_key');
    } else {
      $key = $secretconfig->get('stripe_api_test_secret_key');
    }

    $params = array(
        "amount" => $amount, 
        "currency" => $checkoutconfig->get('stripe_checkout-currency'),
        "source" => $token,
        "description" => $checkoutconfig->get('stripe_checkout-description'),
        "metadata" => array('email' => $email),
        );
    $charge = stripe_api_call('charge', 'create', $params);

    return "<p>".t('We have attempted to charge your card. Thank you for your support!')."</p>";
  } else {
    
    /* No token to work with */
    return "<p>".t('No donation information has been provided. Please try again.')."</p>";
  }


}
