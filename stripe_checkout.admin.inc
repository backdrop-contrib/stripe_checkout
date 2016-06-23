<?php
/**
 * @file
 * Contains implementation of admin settings form for Stripe Checkout
 */

/**
 * Admin form to set up the Stripe Checkout configuration.
 */
 
function stripe_checkout_admin_form() {
  $form = array();
  $config = config('stripe_checkout.settings');

  $form['donateblock-enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the Stripe Checkout Donate Block'),
    '#default_value' => $config->get('donateblock-enabled'),
  );
  
  $form['default-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Stripe Checkout Donate Block Settings'),
    '#description' => t("Configure the Stripe Checkout default settings here."),
    '#collapsible' => TRUE,
    '#collapsed' => 0,
    ),
  );

  // Image type.
  $form['default-settings']['default_image_type'] = array(
    '#type' => 'radios',
    '#title' => t('Image type'),
    '#options' => array(
      'none' => t('No image'),
      'file' => t('Custom image upload'),
      'url' => t('Custom image URL'),
    ),
    '#default_value' => $config->get('default_image_type'),
    '#required' => TRUE,
  );

  // Image upload.
  $form['default-settings']['default_image_file'] = array(
    '#type' => 'managed_file',
    '#title' => t('Logo or Image upload'),
    '#description' => t('Select an png, jpg, or gif image with a minimum size of 128x128px.'),
    '#default_value' => $config->get('default_image_file'),
    '#upload_location' => 'public://stripe_checkout_image/',
    '#upload_validators' => array(
      'file_validate_image_resolution' => array(0, '128x128'),
      'file_validate_extensions' => array('png jpg gif'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="default_image_type"]' => array('value' => 'file'),
      ),
    ),
  );
  if (module_exists('media')) {
    $form['default-settings']['default_image_file']['#type'] = 'media';
  }

  // Image URL.
  $form['default-settings']['default_image_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Logo or Image URL'),
    '#description' => t('Enter an external URL or an internal path to a square image of your brand or product. It should be a png, jpg, or gif image with a minimum size of 128x128px.'),
    '#default_value' => $config->get('default_image_url'),
    '#states' => array(
      'visible' => array(
        ':input[name="default_image_type"]' => array('value' => 'url'),
      ),
    ),
  );

  $form['default-settings']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('Enter the name of your organization or website. (Defaults to your website name if left blank).'),
    '#default_value' => $config->get('name'),
  );

  $form['default-settings']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('Enter the description of what the donation will be used for or what they are donating towards.'),
    '#default_value' => $config->get('description'),
  );
  
  $form['default-settings']['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Default amount'),
    '#description' => t('Enter the default amount that should show in the amount field, in cents. (2000 = $20).'),
    '#default_value' => $config->get('amount'),
  );
  
  $form['default-settings']['currency'] = array(
    '#type' => 'select',
    '#title' => t('Currency'),
    '#description' => t('Select the currency. (If you need help with currencies, <a href="!url">see here</a>. Defaults to USD.', array(
      '!url' => 'https://support.stripe.com/questions/which-currencies-does-stripe-support',
    )),
    '#options' => array(
      'AED' => 'United Arab Emirates Dirham',
      'ALL' => 'Albanian Lek',
      'ANG' => 'Netherlands Antillean Gulden',
      'ARS' => 'Argentine Peso**',
      'AUD' => 'Australian Dollar',
      'AWG' => 'Aruban Florin',
      'BBD' => 'Barbadian Dollar',
      'BDT' => 'Bangladeshi Taka',
      'BIF' => 'Burundian Franc',
      'BMD' => 'Bermudian Dollar',
      'BND' => 'Brunei Dollar',
      'BOB' => 'Bolivian Boliviano**',
      'BRL' => 'Brazilian Real**',
      'BSD' => 'Bahamian Dollar',
      'BWP' => 'Botswana Pula',
      'BZD' => 'Belize Dollar',
      'CAD' => 'Canadian Dollar',
      'CHF' => 'Swiss Franc',
      'CLP' => 'Chilean Peso**',
      'CNY' => 'Chinese Renminbi Yuan',
      'COP' => 'Colombian Peso**',
      'CRC' => 'Costa Rican Colón**',
      'CVE' => 'Cape Verdean Escudo**',
      'CZK' => 'Czech Koruna**',
      'DJF' => 'Djiboutian Franc**',
      'DKK' => 'Danish Krone',
      'DOP' => 'Dominican Peso',
      'DZD' => 'Algerian Dinar',
      'EGP' => 'Egyptian Pound',
      'ETB' => 'Ethiopian Birr',
      'EUR' => 'Euro',
      'FJD' => 'Fijian Dollar',
      'FKP' => 'Falkland Islands Pound**',
      'GBP' => 'British Pound',
      'GIP' => 'Gibraltar Pound',
      'GMD' => 'Gambian Dalasi',
      'GNF' => 'Guinean Franc**',
      'GTQ' => 'Guatemalan Quetzal**',
      'GYD' => 'Guyanese Dollar',
      'HKD' => 'Hong Kong Dollar',
      'HNL' => 'Honduran Lempira**',
      'HRK' => 'Croatian Kuna',
      'HTG' => 'Haitian Gourde',
      'HUF' => 'Hungarian Forint**',
      'IDR' => 'Indonesian Rupiah',
      'ILS' => 'Israeli New Sheqel',
      'INR' => 'Indian Rupee**',
      'ISK' => 'Icelandic Króna',
      'JMD' => 'Jamaican Dollar',
      'JPY' => 'Japanese Yen',
      'KES' => 'Kenyan Shilling',
      'KHR' => 'Cambodian Riel',
      'KMF' => 'Comorian Franc',
      'KRW' => 'South Korean Won',
      'KYD' => 'Cayman Islands Dollar',
      'KZT' => 'Kazakhstani Tenge',
      'LAK' => 'Lao Kip**',
      'LBP' => 'Lebanese Pound',
      'LKR' => 'Sri Lankan Rupee',
      'LRD' => 'Liberian Dollar',
      'MAD' => 'Moroccan Dirham',
      'MDL' => 'Moldovan Leu',
      'MNT' => 'Mongolian Tögrög',
      'MOP' => 'Macanese Pataca',
      'MRO' => 'Mauritanian Ouguiya',
      'MUR' => 'Mauritian Rupee**',
      'MVR' => 'Maldivian Rufiyaa',
      'MWK' => 'Malawian Kwacha',
      'MXN' => 'Mexican Peso**',
      'MYR' => 'Malaysian Ringgit',
      'NAD' => 'Namibian Dollar',
      'NGN' => 'Nigerian Naira',
      'NIO' => 'Nicaraguan Córdoba**',
      'NOK' => 'Norwegian Krone',
      'NPR' => 'Nepalese Rupee',
      'NZD' => 'New Zealand Dollar',
      'PAB' => 'Panamanian Balboa**',
      'PEN' => 'Peruvian Nuevo Sol**',
      'PGK' => 'Papua New Guinean Kina',
      'PHP' => 'Philippine Peso',
      'PKR' => 'Pakistani Rupee',
      'PLN' => 'Polish Złoty',
      'PYG' => 'Paraguayan Guaraní**',
      'QAR' => 'Qatari Riyal',
      'RUB' => 'Russian Ruble',
      'SAR' => 'Saudi Riyal',
      'SBD' => 'Solomon Islands Dollar',
      'SCR' => 'Seychellois Rupee',
      'SEK' => 'Swedish Krona',
      'SGD' => 'Singapore Dollar',
      'SHP' => 'Saint Helenian Pound**',
      'SLL' => 'Sierra Leonean Leone',
      'SOS' => 'Somali Shilling',
      'STD' => 'São Tomé and Príncipe Dobra',
      'SVC' => 'Salvadoran Colón**',
      'SZL' => 'Swazi Lilangeni',
      'THB' => 'Thai Baht',
      'TOP' => 'Tongan Paʻanga',
      'TTD' => 'Trinidad and Tobago Dollar',
      'TWD' => 'New Taiwan Dollar',
      'TZS' => 'Tanzanian Shilling',
      'UAH' => 'Ukrainian Hryvnia',
      'UGX' => 'Ugandan Shilling',
      'USD' => 'United States Dollar',
      'UYU' => 'Uruguayan Peso**',
      'UZS' => 'Uzbekistani Som',
      'VND' => 'Vietnamese Đồng',
      'VUV' => 'Vanuatu Vatu',
      'WST' => 'Samoan Tala',
      'XAF' => 'Central African Cfa Franc',
      'XOF' => 'West African Cfa Franc**',
      'XPF' => 'Cfp Franc**',
      'YER' => 'Yemeni Rial',
      'ZAR' => 'South African Rand',
    ),
    '#default_value' => $config->get('currency'),
    '#required' => TRUE,
  );
  
  $form['default-settings']['locale'] = array(
    '#type' => 'select',
    '#title' => t('Locale'),
    '#description' => t('Specify "auto" to display Checkout in the <a href="!url">user\'s preferred language</a>, if available.', array(
      '!url' => 'https://support.stripe.com/questions/what-languages-does-stripe-checkout-support',
    )),
    '#default_value' => $config->get['locale'],
    '#options' => array(
      'auto' => t('auto'),
      'zh' => t('Chinese'),
      'nl' => t('Dutch'),
      'en' => t('English'),
      'fr' => t('French'),
      'de' => t('German'),
      'it' => t('Italian'),
      'ja' => t('Japanese'),
      'es' => t('Spanish'),
    ),
  );

  $form['default-settings']['zip'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require Zip Code'),
    '#default_value' => $config->get('zip'),
  );

  $form['default-settings']['billing-addr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require a Billing Address'),
    '#default_value' => $config->get('billing-addr'),
  );

  $form['default-settings']['shipping-addr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require a Shipping Address (This information will be available in the Stripe dashboard payment transaction)'),
    '#default_value' => $config->get('shipping-addr'),
  );

  $form['default-settings']['outer-button'] = array(
    '#type' => 'textfield',
    '#title' => t('Outer/Initial Button Text'),
    '#description' => t('Enter the text to show on the first button. Default: <strong>Donate now.</strong>'),
    '#default_value' => $config->get('outer-button'),
  );
  
  $form['default-settings']['inner-button'] = array(
    '#type' => 'textfield',
    '#title' => t('Inner/Submit Button Text'),
    '#description' => t('Enter the text to show on the inner/submit button. Default: <strong>Donate {{amount}}.</strong>'),
    '#default_value' => $config->get('inner-button'),
  );

  $form['default-settings']['prefill-email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prefill email address'),
    '#description' => t('If the user is logged in, should we prefill the email address from their Backdrop account?'),
    '#default_value' => $config->get('prefill-email'),
  );

  $form['default-settings']['allow-remember-me'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include option to "Remember Me" for future purchases'),
    '#default_value' => $checkout_settings['allow-remember-me'],
  );
  
  $form['default-settings']['bitcoin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Accept Bitcoin payments'),
    '#default_value' => $checkout_settings['bitcoin'],
  );
  
  $form['default-settings']['alipay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Accept Alipay payments'),
    '#default_value' => $checkout_settings['alipay'],
  );
  
  $form['default-settings']['alipay-reusable'] = array(
    '#type' => 'checkbox',
    '#title' => t("Request reusable access to customer's Alipay account"),
    '#default_value' => $checkout_settings['alipay-reusable'],
    '#states' => array(
      'visible' => array(
        ':input[name="stripe_checkout_webform_checkout_settings[alipay]"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  
  return $form;
}

/**
 * Validation callback for stripe_checkout_admin_form().
 */
function stripe_checkout_admin_form_validate($form, &$form_state) {
  $name = 'amount' ;
  if (!empty($form_state['values'][$name]) && !is_numeric($form_state['values'][$name])) {
    form_set_error($name, t('The default amount has to be a number.'));
  }
}

/**
 * Submit handler for stripe_checkout_admin_form().
 */
function stripe_checkout_admin_form_submit($form, &$form_state) {
  $config = config('stripe_checkout.settings');
  $values = $form_state['values'];

  if (isset($values['image']) && $values['image']) {
    $file = file_load($values['image']);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    file_usage_add($file, 'stripe_checkout', 'Stripe Checkout Config', $values['image']);
  }
  $config->set('donateblock-enabled' , $values['donateblock-enabled']);
  $config->set('default_image_type' , $values['default_image_type']);
  $config->set('default_image_file' , $values['default_image_file']);
  $config->set('default_image_url' , $values['default_image_url']);
  $config->set('currency' , $values['currency']);
  $config->set('locale' , $values['locale']);
  $config->set('zip' , (bool)$values['zip']);
  $config->set('billing-addr' , (bool)$values['billing-addr']);
  $config->set('shipping-addr' , (bool)$values['shipping-addr']);
  $config->set('prefill-email' , (bool)$values['prefill-email']);
  $config->set('allow-remember-me' , (bool)$values['allow-remember-me']);
  $config->set('bitcoin' , (bool)$values['bitcoin']);
  $config->set('alipay' , (bool)$values['alipay']);
  $config->set('alipay-reusable' , (bool)$values['alipay-reusable']);
  $config->set('outer-button' , $values['outer-button']);
  $config->set('inner-button' , $values['inner-button']);
  $config->set('name' , $values['name']);
  $config->set('description' , $values['description']);
  $config->set('amount' , intval($values['amount']));
  $config->save();

  backdrop_set_message(t('Stripe Checkout settings have been saved.'));
}






